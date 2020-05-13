/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_libtest02.c */

#include <stdio.h>
#include "aurrem_testlib02.h"

int main() {
	int result = sum(5, 12);
	printf("%d", result);
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
}