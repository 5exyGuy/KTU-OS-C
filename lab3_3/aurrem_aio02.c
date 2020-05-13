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
int aioRead(struct aiocb *aiocbp);
int testDummy(const void* data, int n);
int aioSuspend(const struct aiocb* aiorp);
int aioReturn(struct aiocb *aiocbp);
int readBytes(int desc, struct aiocb* block, char* buf, int bufOffset, int bytes);
int ps_read_wait(struct aiocb *block);

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

int aioRead(struct aiocb *aiocbp) {
    int rv = aio_read(aiocbp);
    if(rv == -1){
        perror("aioRead failed");
        abort();
    }
    return rv;
}

int testDummy(const void* data, int n) {
    int cnt = 0;
    for(int i = 0; i < n; i++)
        if(((char*)data)[i] == '\0') cnt++;
    printf("Number of '0' in data: %d\n", cnt);
    return 1;
}

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

int readBytes(int desc, struct aiocb* block, char* buf, int bufOffset, int bytes) {
    memset((void*) block, 0, sizeof(struct aiocb));
    block->aio_fildes = desc;
    block->aio_buf = buf + bufOffset;
    block->aio_nbytes = bytes;
    block->aio_offset = 0;
    if (aioRead(block) != 0){
        perror("readBytes failed");
        return -1;
    }
    return 0;
}

int readWait(struct aiocb* block) {
    const struct aiocb *temp[1];
    temp[0] = block;

    if (aioSuspend(block) != 0){
        perror("readWait failed");
        return -1;
    }

    return aioReturn(block);
}

int main(){
    struct aiocb aior;
    char buffer[BUFFLEN];
    int n = 0, t;
    int d = openFile("/dev/urandom", O_RDONLY);
	
    while (n < BUFFLEN) {
        if (readBytes(d, &aior, buffer, n, BUFFLEN - n) != 0)
			exit(EXIT_FAILURE);

		t = readWait(&aior);
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