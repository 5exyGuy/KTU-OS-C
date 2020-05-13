/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_misc01.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int createDir(const char* dirName);
int givePerms(const char* fileName, mode_t perms);

int createDir(const char* dirName) {
	return mkdir(dirName, S_IRUSR);
}

int givePerms(const char* fileName, mode_t perms) {
	return chmod(fileName, perms);
}

int main(int argc, char* argv[]) {
	printf("%d", createDir(argv[1]));
	printf("%d", givePerms(argv[1], S_IWUSR | S_IRUSR | S_IXUSR));
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}
