/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: loginas_pathconf.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
   long maxFileLength;
   if (maxFileLength = pathconf("/", _PC_NAME_MAX) != -1)
      printf("Maksimalus failo vardo ilgis: %ld\n", maxFileLength);
   else {
      perror("pathconf failed");
      abort();
   }

   long maxPathLength;
   if (maxFileLength = pathconf("/", _PC_PATH_MAX) != -1)
      printf("Maksimalus kelio ilgis: %ld\n", maxPathLength);
   else {
      perror("pathconf failed");
      abort();
   }

   printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
   return 0;
}
