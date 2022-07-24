#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "t_params.h"
#define __NR_set_total_computation_time 341
#define __NR_get_remaining_time 342

int main(void)
{
	printf("Trap to kernel level\n");
	struct t_params *new;
	new=malloc(sizeof(struct t_params));
	syscall(__NR_set_total_computation_time,-1,42);
	syscall(__NR_get_remaining_time,-1,new);
/* you should check return value for errors */
	printf("Back to user level\n");
}
