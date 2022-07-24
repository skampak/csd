/*Sofia Kampaki,am 3221 */
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include <assert.h>

/*returns the pcstr length*/
size_t ms_length(const char pcstr[])
{
  size_t length=0U;
  assert(pcstr);
  while(pcstr[length])
    length++;
  return length;
}
/*copies the pcstr string at the npcstr*/
char *ms_copy(char npcstr[],const char pcstr[])
{ 
   int k;
   size_t l=ms_length(pcstr);
   assert(pcstr);
   for(k=0;k<l;k++){
	   npcstr[k]=pcstr[k];
   }
   npcstr[k]='\0';
   return npcstr;
}

/*copies the first n chars of pcstr string at the npcstr string  npctr becomes pcstr*/
char *ms_ncopy(char npcstr[],const char pcstr[], size_t n)
{
  
  size_t j=0U;
  assert(pcstr);
  while(n>0 && pcstr[j]!='\0'){
	  npcstr[j]=pcstr[j];
	  j++;
	 n--;
  }
  printf("lol:%s\n",npcstr);
  return npcstr;
}

/*copies the chars of the pcstr at the END of the npcstr string*/
char *ms_concat(char npcstr[],const char pcstr[])
{
  ms_copy(npcstr + ms_length(npcstr),pcstr);
  return npcstr;
}

/*copies the first n chars of pcstr string at the end of the npcstr*/
char *ms_nconcat(char npcstr[], const char pcstr[], size_t n)
{
  
  size_t i = ms_length(npcstr);
  size_t k=0U;
  assert(pcstr);
 
  while(n>0){
	  npcstr[i]=pcstr[k];
	  k++;
	  i++;
	  n--;
	}
	if(npcstr[i]!='\0'){
		npcstr[i]='\0';
	}
    
    return npcstr;
  
}

/*compares  the pcstr and npcstr  strings.while they are the same
 the function continues */
int ms_compare(const char pcstr[],const char npcstr[])
{
   char x1;
   char x2;
   size_t i=0U;
   size_t k=0U;
  while(pcstr[i]!= '\0' && (pcstr[i]==npcstr[k])){
       i++;
       k++;
  }
  x1=pcstr[i];
  x2=npcstr[k];
  if(x1-x2==0)
	  return 0;
  else
	  return 1;
  
}


int ms_ncompare(const char pcstr[],const char npcstr[],size_t n)
{
  char x1;
  char x2;
  size_t i=0U;
  size_t k=0U;
  while(n>0){
   if(pcstr[i++]!=npcstr[k++]){
	    x1=pcstr[i];
       x2=npcstr[k];
	   n--;
   }
   
  }
   if(x1-x2==0)
       return 0;
   else
  return 1;
   
}

/*checks if the npcstr string is at the pcstr one*/
char *ms_search( char pcstr[], const char npcstr[])
{
  size_t n = ms_length(npcstr);
  size_t i = 0U;
 
  assert(pcstr);
  assert(npcstr);
  
  while(pcstr[i] != '\0'){
	  
	  printf("pcstr is %s\n",pcstr);
     if(ms_ncompare(pcstr,npcstr,n)==0){
		  
		 return (char *)pcstr-1;
       
	 }
	 pcstr++;
	
	 
  }
  return NULL;
  
}
