/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_getcwd2.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int openFile(const char* path, const int flags);
char* getCWDPath();
void changeDir(const char* path);
void changeDirFd(int fd);

int openFile(const char* path, const int flags) {
   int d = open(path, flags);
   if (d == -1) {
      perror("openFile failed");
      exit(EXIT_FAILURE);
   }

   return d;
}

void changeDir(const char* path) {
   if (chdir(path) == -1) {
      perror("changeDir failed");
      abort();
   }
}

void changeDirFd(int fd) {
   if (fchdir(fd) == -1) {
      perror("changeDirFd failed");
      abort();
   }
}

char* getCWDPath(char* path) {
   char* cwd = getcwd(NULL, pathconf(path, _PC_PATH_MAX)); 
   if (cwd == NULL) {
      perror("getPath failed");
      abort();
   }

   return cwd;
}

int main(int argc, char* argv[]) {
   char* cwd = getCWDPath(".");
   puts(cwd);

   int fileDescriptor = openFile(cwd, O_RDONLY);

   changeDir("/tmp");
   cwd = getCWDPath(".");
   puts(cwd);

   changeDirFd(fileDescriptor);
   cwd = getCWDPath(".");
   puts(cwd);

   printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
   return 0;
}
