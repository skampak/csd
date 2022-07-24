#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <linux/limits.h>

int main(int argc, char *argv[]){

	char const* const logfile = argv[2];
	FILE *fd;
	char line[256];
	size_t len = 0;
	ssize_t nread;
	char ch;
	int lines;

	int i=0;
	int lsize,opt,flag;
	printf("%s\n", argv[1]);
	
	
	



	while((opt =  getopt(argc, argv, "i:m:h")) != -1){
		switch(opt){
			case 'i':
				flag = 0;
				break;
			case 'm':
				flag = 1;
				break;
			case 'h':
				printf(" help message\n");
				break;
			default:
				printf("lalal\n");
		}
	}
	fd = fopen(logfile,"r");

	if(fd == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}




	char data[500][7][50];
	char *tmp;
	int cnt=0;
		while(fgets(line,sizeof(line),fd)){

		sscanf(line, "%s%s%s%s%s%s%s", data[i][0], data[i][1], data[i][2],data[i][3],data[i][4],data[i][5],data[i][6]);
		i++;
	}
	if(flag = 1){
	for(i=0;i<500;i++){
		if(strcmp(data[i][5],"1")==0){
			printf("user %s is malicious on file %s\n", data[i][0], data[i][1]);
		}
	}
	}else if(flag = 0){
		for(i = 0; i<500; i++){
		tmp = data[i][6];
		if(strcmp(data[i][1],argv[2])==0){
			
			if(strcmp(tmp,data[i][6])!=0){
				cnt++;
			}
			printf("user %s accessed file %s times %d\n", data[i][0], data[i][1],cnt);
		}
		}
	}

	fclose(fd);


	return 0;
}
