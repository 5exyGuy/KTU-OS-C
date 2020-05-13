/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_readdir01.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <inttypes.h>

DIR* openDir(const char* path);
void closeDir(DIR* dir);

DIR* openDir(const char* path) {
   DIR* dir = opendir(path);
   if (dir == NULL) {
      perror("openDir failed");
      exit(EXIT_FAILURE);
   }

   return dir;
}

void closeDir(DIR* dir) {
   if (closedir(dir) == -1) {
      perror("closeDir failed");
      exit(EXIT_FAILURE);
   }
}

int main(int argc, char* argv[]) {
   DIR* dir = openDir(".");

   struct dirent* dp;

   while ((dp = readdir(dir)) != NULL) {
      printf("%ju %s\n", (uintmax_t) dp->d_ino, dp->d_name);
   }

   closeDir(dir);

   printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
   return 0;
}
