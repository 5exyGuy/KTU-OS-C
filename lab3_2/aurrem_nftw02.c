/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_nftw02.c */

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>

void treeWalk(const char* path, int nopenfd, int flags);
int treeInfo(const char* p, const struct stat* st, int fl, struct FTW* fbuf);

int treeInfo(const char* p, const struct stat* st, int fl, struct FTW* fbuf) {
	if (S_ISREG(st->st_mode))
		printf("%s\n", p + fbuf->base);	
	return 0;
}

void treeWalk(const char* path, int nopenfd, int flags) {
   int rv = nftw(getenv("HOME"), treeInfo, nopenfd, flags);
   if (rv == -1) {
      perror("treeWalk failed");
      exit(EXIT_FAILURE);
   }

   if(rv != 0)
      printf("ntfw fn function returnd %d != 0 -> nftw finished\n", rv);
}

int main(int argc, char* argv[]) {
   treeWalk(getenv("HOME"), 20, FTW_PHYS);
   return 0;
}
