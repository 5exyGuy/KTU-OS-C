/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_seek01.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int createFile(const char* fileName, int flags);
off_t repositionFileOffset(int fd, off_t offset, int whence);
ssize_t writeFile(int fd, const void *buf, size_t count);
void closeFile(int fd);

int createFile(const char* fileName, int flags) {
	int dskr = creat(fileName, flags);
	if (dskr == -1) {
		perror("createFile failed");
		exit(1);
	}
	printf("Descriptor = %d\n", dskr);
	return dskr;
}

off_t repositionFileOffset(int fd, off_t offset, int whence) {
	off_t offs = lseek(fd, offset, whence);
	if (offs == -1) {
		perror("repositionFileOffset failed");
		exit(EXIT_FAILURE);
	}
	return offs;
}

ssize_t writeFile(int fd, const void *buf, size_t count) {
	ssize_t size = write(fd, &buf, count);
	if (size == -1) {
		perror("writeFile failed");
		exit(EXIT_FAILURE);
	}
	return size;
}

void closeFile(int fd) {
	if (close(fd) == -1) {
		perror("closeFile failed");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	int file = createFile(argv[1], 0777);

	repositionFileOffset(file, 1048576, SEEK_SET);
	writeFile(file, &file, 1);
	closeFile(file);
	
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}
