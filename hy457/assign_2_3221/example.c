#include <stdio.h>

int main (void){
	//printf("Calling the fopen() function...\n");
	char str[]= "WriteSomething\0\n";
	FILE *fd = fopen("fileno0.txt","w");
	if(!fd) {
		printf("fopen() returned NULL\n");
		return 1;
	}

	fwrite(str,1,sizeof(str),fd);
	printf("fopen() succeeded\n");
	return 0;
}
