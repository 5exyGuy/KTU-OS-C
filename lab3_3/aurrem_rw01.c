/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_rw01.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int openFile(const char* fileName, int flags);
int closeFile(int fd);
void copyFileContentTo(int source, int target, int size);

int openFile(const char* fileName, int flags) {
	int dskr = open(fileName, flags);
	if(dskr == -1){
		perror("openFile failed");
		exit(EXIT_FAILURE);
	}
	printf("dskr = %d\n", dskr);
	return dskr;
}

int closeFile(int fd) {
	int rv = close(fd);
	if(rv != 0) perror("closeFile failed");
	else puts("closed");
	return rv;
}

void copyFileContentTo(int source, int target, int size) {
	struct stat sb;

	if (fstat(source, &sb) == -1) {
		perror("fstat failed");
		exit(EXIT_FAILURE);
	}

	if (sb.st_size < size) size = sb.st_size;

	char buf[size];
	
	read(source, buf, size);
	write(target, buf, size);
}

int main(int argc, char* argv[]) {
	int oFile = openFile(argv[1], O_RDONLY);
	int wFile = openFile(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
	copyFileContentTo(oFile, wFile, atoi(argv[3]));
	closeFile(oFile);
	closeFile(wFile);
	
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}
