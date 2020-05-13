/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_stat01.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getFileType(struct stat sb);
char* getFilePerms(struct stat sb);
struct stat getFileStat(const char* path);

char* getFileType(struct stat sb) {
   switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:  return "block device";
      case S_IFCHR:  return "character device";
      case S_IFDIR:  return "directory";
      case S_IFIFO:  return "FIFO/pipe";
      case S_IFLNK:  return "symlink";
      case S_IFREG:  return "regular file";
      case S_IFSOCK: return "socket";
      default:       return "unknown";
   }
   return "unknown";
}

char* getFilePerms(struct stat sb) {
   char* modeval = malloc(sizeof(char) * 8 + 1);
   mode_t perm = sb.st_mode;

   modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
   modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
   modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
   modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
   modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
   modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
   modeval[6] = (perm & S_IROTH) ? 'r' : '-';
   modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
   modeval[8] = (perm & S_IXOTH) ? 'x' : '-';

   return modeval;
}

struct stat getFileStat(const char* path) {
   struct stat sb;

   if (stat(path, &sb) == -1) {
      perror("getFileStat failed");
      exit(EXIT_FAILURE);
   }

   return sb;
}

int main(int argc, char* argv[]) {
   struct stat sb = getFileStat(argv[1]);

   printf("Savininkas: %ld\n", (long) sb.st_uid);
   printf("I-node numeris: %ld\n", (long) sb.st_ino);
   printf("Failo dydis: %lld baitų\n", (long long) sb.st_size);
   printf("Leidimai: %s\n", getFilePerms(sb));
   printf("Failo tipas: %s\n", getFileType(sb));

   printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
   return 0;
}
