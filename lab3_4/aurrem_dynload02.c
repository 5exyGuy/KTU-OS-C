/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_dynload02.c */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int (*fptr)(int x, int y);

int main(){
	void *dl;
	
	dl = dlopen("libfoo.so", RTLD_LAZY | RTLD_LOCAL);
	if (dl == NULL) {
		puts(dlerror());
		exit(1);
	}
	
	*(void**)(&fptr) = dlsym(dl, "sum");
	if (fptr == NULL) {
		puts(dlerror());
		exit(1);
	}
	
	int result = (*fptr)(5, 20);
	printf("Rezultatas: %d\n", result);
	
	dlclose(dl);
	
	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}