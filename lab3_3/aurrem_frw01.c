/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_frw01.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE* openFile(const char* fileName, const char* mode);
int closeFile(FILE* file);
void copyFileContentTo(FILE* source, FILE* target, const int size);

FILE* openFile(const char* fileName, const char* mode) {
	FILE* fp = fopen(fileName, mode);
	if(fp == NULL){
		perror("openFile");
		exit(1);
	}
	return fp;
}

int closeFile(FILE* file) {
	if(fclose(file) == EOF) 
		perror("closeFile failed");
	else 
		puts("closed");
	return 0;
}

void copyFileContentTo(FILE* source, FILE* target, const int size) {
	char buf[size];
	//size_t nread = size;
	size_t nread = sizeof(buf);
	
	fread(buf, nread, 1, source);
	fwrite(buf, nread, 1, target);
}

int main(int argc, char* argv[]) {
	FILE* oFile = openFile(argv[1], "r");
	FILE* wFile = openFile(argv[2], "w");
	copyFileContentTo(oFile, wFile, atoi(argv[3]));
	closeFile(oFile);
	closeFile(wFile);
	
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}
