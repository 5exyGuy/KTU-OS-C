/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_exit01.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f1();
void f2();
void f3();
void f4();

void f1() {
	printf("F1\n");
	_Exit(1);
}

void f2() {
	printf("F2\n");
	exit(1);
}

void f3() {
	printf("F3\n");
	abort();
}

void f4() {
	printf("F4\n");
	return;
}

int main(int argc, char *argv[]) {
	atexit(f1);
	atexit(f2);
	atexit(f3);
	atexit(f4);
	
	printf("Main\n");

	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}