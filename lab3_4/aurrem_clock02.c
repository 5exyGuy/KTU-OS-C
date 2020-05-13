/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_clock02.c */

#include <stdio.h>
#include <time.h>

void printLocalTime();
void printUTCTime();

void printLocalTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Local Time: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void printUTCTime() {
    time_t rawtime = time(&rawtime);
    struct tm tm = *gmtime(&rawtime);
    printf("UTC Time: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main()
{
	printLocalTime();
	printUTCTime();
    printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
  	return 0;
}