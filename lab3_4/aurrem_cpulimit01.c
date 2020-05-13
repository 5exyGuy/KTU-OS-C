/* Aurėjus Remeika IFZ-8/2 aurrem */
/* Failas: aurrem_cpulimit01.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/time.h>

void setCPULimit(int cur, int max);

void setCPULimit(int cur, int max) {
	struct rlimit rl_cpu;
	struct rlimit rl_core;
	
	getrlimit(RLIMIT_CPU, &rl_cpu);
	getrlimit(RLIMIT_CORE, &rl_core);
	
	printf("RLIMIT_CPU %ld (soft) %ld (hard)\n", rl_cpu.rlim_cur, rl_cpu.rlim_max);
	printf("RLIMIT_CORE %ld (soft) %ld (hard)\n", rl_core.rlim_cur, rl_core.rlim_max);

	rl_cpu.rlim_cur = cur;
	rl_cpu.rlim_max = max;
	
	rl_core.rlim_cur = 0;
	rl_core.rlim_max = 0;

	setrlimit(RLIMIT_CPU, &rl_cpu);
	setrlimit(RLIMIT_CPU, &rl_core);
	
	getrlimit(RLIMIT_CORE, &rl_cpu);
	getrlimit(RLIMIT_CORE, &rl_core);

	printf("RLIMIT_CPU %ld (soft) %ld (hard)\n", rl_cpu.rlim_cur, rl_cpu.rlim_max);
	printf("RLIMIT_CORE %ld (soft) %ld (hard)\n", rl_core.rlim_cur, rl_core.rlim_max);	
}

int main(int argc, char *argv[]) {
	setCPULimit(0, 1);

	int count = 0;

	while(1) {
		count++;
	}

	printf("(C) 2020 Aurėjus Remeika, %s\n", __FILE__);
	return 0;
}