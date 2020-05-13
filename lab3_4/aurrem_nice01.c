/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_nice01.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int delay(int inc);

int delay(int inc) {
    clock_t start = clock();
    for(int i = 0; i < 0x7FFFFFFF; i++);
    clock_t end = clock();
    clock_t diff = end - start;
    printf("CLOCKS_PER_SEC = %ld\n start=%ld\n end=%ld\n diff=%ld, diff(s)=%f\n",
        (long)CLOCKS_PER_SEC, (long)start, (long)end, (long)diff, (double)diff / CLOCKS_PER_SEC);
    return 1;
}

int main(int argc, char* argv[]) {
    clock_t start;
    delay(atoi(argv[1]));
    clock_t end;
    unsigned long millis = (end - start) / CLOCKS_PER_SEC;
    printf("CPU TIME: %lu\n", millis);
    printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
    return 0;
}