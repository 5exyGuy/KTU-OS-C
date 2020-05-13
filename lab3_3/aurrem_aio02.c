/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_aio02.c */

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#define BUFFLEN 1048576

int openFile(const char* path, int flags);
int closeFile(int fd);
int aioRead(int desc, struct aiocb* aior, char* buf, int bufOffset, int bytes)
// int testDummy(const void* data, int n);
int aioSuspend(const struct aiocb* aiorp);
int aioReturn(struct aiocb *aiocbp);
int aioRead(int desc, struct aiocb* aior, char* buf, int bufOffset, int bytes);
int aioWait(struct aiocb* aior)

int openFile(const char* path, int flags) {
    int d = open(path, flags);
    if(d == -1) {
        perror("openFile failed");
        exit(EXIT_FAILURE);
    }
    if(__INCLUDE_LEVEL__ == 0)
        printf("Descriptor = %d\n", d);
    return d;
}

int closeFile(int fd){
    int rv = close(fd);
    if(rv != 0) perror("closeFile failed");
    else puts("closeFile successed");
    return rv;
}

// int testDummy(const void* data, int n) {
//     int cnt = 0;
//     for(int i = 0; i < n; i++)
//         if(((char*)data)[i] == '\0') cnt++;
//     printf("Number of '0' in data: %d\n", cnt);
//     return 1;
// }

int aioSuspend(const struct aiocb* aiorp) {
    const struct aiocb *aioptr[1];
	aioptr[0] = aiorp;
	int rv = aio_suspend(aioptr, 1, NULL);
	if(rv != 0){
	  perror("aioSuspend failed");
	  abort();
	}
    return rv;
}

int aioReturn(struct aiocb *aiocbp) {
    int rv = aio_return(aiocbp);
    if (rv == -1) {
        perror("aioReturn failed");
        abort();
    }
    return rv;
}

int aioRead(int desc, struct aiocb* aior, char* buf, int bufOffset, int bytes) {
    memset((void*) aior, 0, sizeof(struct aiocb));
    aior->aio_fildes = desc;
    aior->aio_buf = buf + bufOffset;
    aior->aio_nbytes = bytes;
    aior->aio_offset = 0;

	int rv = aio_read(aior);
	if(rv == -1){
		perror("aioRead failed");
		abort();
	}

    return rv;
}

int aioWait(struct aiocb* aior) {
    const struct aiocb *temp[1];
    temp[0] = aior;

    if (aioSuspend(aior) != 0){
        perror("readWait failed");
        return -1;
    }

    return aioReturn(aior);
}

int main(){
    struct aiocb aior;
    char buffer[BUFFLEN];
    int n = 0, t = 0;
    int d = openFile("/dev/urandom", O_RDONLY);
	
    while (n < BUFFLEN) {
		if (aioRead(d, &aior, buffer, n, BUFFLEN - n) != 0)
			exit(EXIT_FAILURE);

		t = aioWait(&aior);
        if (t > 0) {
            n += t;
            printf("%d bytes\n", n);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);

    return 0;
}