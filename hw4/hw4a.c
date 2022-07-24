#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	
    int *frequency,i,g,j,N,pos,S,maxnumber,result;
    char **wordsarray;
	printf("Give a number of words:");
	scanf("%d",&N);	
	wordsarray=(char**)malloc(N*sizeof(char*));
	if (wordsarray==NULL)
	{
		printf("Unable to allocate enough memory!\n");
		exit(1);
	} 
	for (j=0;j<N;j++)
	{
		wordsarray[j]=(char*)malloc(N*sizeof(char));
		if(wordsarray[j]==NULL)
    	{
		printf("Unable to allocate enough memory!\n");
		exit(1);
    	}  
	}
	for(i=0;i<N;i++){
		scanf("%s",wordsarray[i]);
	}
	frequency=(int*)malloc(N*sizeof(int));
	if(!frequency){
	printf("Unable to allocate enough memory!");		
	}
	for(i=0;i<N;i++) {
		S=0;
		for(g=i;g<N;g++) {
		  result=strcmp(wordsarray[i],wordsarray[g]);    
		  if(result==0) {
		  	S=S+1;		  	          	 
	}
	}			
	frequency[i]=S;	  
	}	
   maxnumber=frequency[0];
   pos=0;
   for(i=0;i<N;i++){
	if(frequency[i]>maxnumber){
		maxnumber=frequency[i];
		pos=i;
       }
   } 
   printf("%s",wordsarray[pos]);
   for(j=0;j<N;j++)
   {
   	free(wordsarray[j]);   
   } 
   free(wordsarray);
   
}
