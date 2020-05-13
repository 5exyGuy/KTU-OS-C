/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_mmap02.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int openFile(const char* path, int flags);
int closeFile(int fd);
struct stat getFileStatus(int fd);
void truncateFile(int fd, off_t length);
void* mapFile(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
int unmapFile(void* addr, int size);
void* copyMemory(void* dest, const void* src, size_t n);

int openFile(const char* path, int flags) {
	int d = open(path, flags);
	
	if (d == -1) {
		perror("openFile failed");
		exit(EXIT_FAILURE);
	}
	
	printf("Descriptor = %d\n", d);
	
	return d;
}

int closeFile(int fd) {
	int rv = close(fd);
	if(rv != 0) perror("closeFile failed");
	else puts("closed");
	return rv;
}

struct stat getFileStat(int fd) {
	struct stat finfo;
	
	if (fstat(fd, &finfo) == -1) {
		perror("getFileStat failed");
		close(fd);
		exit(EXIT_FAILURE);
	}
	
	return finfo;
}

void truncateFile(int fd, off_t length) {
	int ft = ftruncate(fd, length);
	if (ft == -1) {
		perror("truncateFile failed");
		exit(EXIT_FAILURE);
	}
}

void* mapFile(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
	void* mapf = mmap(addr, length, prot, flags, fd, offset);
	if(mapf == MAP_FAILED) {
        perror("mapFile failed");
        exit(EXIT_FAILURE);
    }
	return mapf;
}

int unmapFile(void* addr, int size) {
   int rv = munmap(addr, size );
   if(rv == -1){
      puts("unmapFile failed");
      abort();
   }
   return rv;
}

void* copyMemory(void* dest, const void* src, size_t n) {
	return memcpy(dest, src, n);
}

int main(int argc, char* argv[]) {
	int rFile = openFile(argv[1], O_RDONLY);
	int wFile = openFile(argv[2], O_RDWR | O_CREAT | O_TRUNC);
	
	struct stat rFileInfo = getFileStat(rFile);
	struct stat wFileInfo = getFileStat(wFile);
	
	printf("%lld\n%lld\n", (long long) rFileInfo.st_size, (long long) wFileInfo.st_size);
	
	truncateFile(wFile, rFileInfo.st_size);
	
	void* rmap = mapFile(NULL, rFileInfo.st_size, PROT_READ, MAP_SHARED, rFile, 0);
	void* wmap = mapFile(NULL, rFileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, wFile, 0);
	
	copyMemory(wmap, rmap, rFileInfo.st_size);
	
	unmapFile(rmap, rFileInfo.st_size);
	unmapFile(wmap, rFileInfo.st_size);

	closeFile(rFile);
	closeFile(wFile);

	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
}
