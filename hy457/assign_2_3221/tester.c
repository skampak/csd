#include <stdlib.h>
#include <stdio.h>


int main(void){

  int i;
  int nf = 2;
  FILE *files[nf];
  for(i = 0; i<nf; i++){
	char fn[20];
	sprintf(fn, "fileno%d.txt" ,i);
	files[i] = fopen(fn,"w");
  }

  return 0;
}
