/*Sofia Kampaki,am 3221 */
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include <assert.h>

/*returns the pcstr length*/
size_t ms_length(const char *pcstr)
{
  const char *pcstrend = pcstr;
  assert(pcstr != NULL);
  while(*pcstrend != '\0')
    pcstrend++;
  return pcstrend - pcstr;
}
/*copies the pcstr string at the npcstr*/
char *ms_copy(char *npcstr,const char *pcstr)
{ 
   char *pcstrend;
   pcstrend=npcstr;
   assert(pcstr);
 while(*pcstr!='\0')
  {
    *pcstrend=*pcstr;
    pcstrend++;
    pcstr++;
  }
    return npcstr;
}

/*copies the first n chars of pcstr string at the npcstr string  npctr becomes pcstr*/
char *ms_ncopy(char *npcstr,const char *pcstr, size_t n)
{
  char *pcstrend = npcstr;
  
  assert(pcstr);
  while(*pcstr != '\0' && n > 0)
  {
     *pcstrend++ = *npcstr++;
      --n;
  }
  while (n>0)
  {
    *pcstrend++ = '\0';
    --n;
  }
  return npcstr;
}

/*copies the chars of the pcstr at the END of the npcstr string*/
char *ms_concat(char *npcstr,const char *pcstr)
{
	ms_copy(npcstr + ms_length(npcstr),pcstr);
	return npcstr;
}

/*copies the first n chars of pcstr string at the end of the npcstr*/
char *ms_nconcat(char *npcstr, const char *pcstr, size_t n)
{
	size_t i;
  char *pcstrend = npcstr;
  assert(pcstr);
  for(i=0;i<ms_length(npcstr);i++){
	  pcstrend++;
  }
  while(n>0){
	  *pcstrend=*pcstr;
	  
	  n--;
	  pcstrend++;
	  pcstr++;
	}
	if(*pcstrend!='\0'){
		*pcstrend='\0';
	}
    
    return npcstr;
}

/*compares  the pcstr and npcstr  strings.while they are the same
 the function continues */
int ms_compare(const char *pcstr,const char *npcstr)
{
  while(*pcstr && (*pcstr==*npcstr))
       pcstr++;
       npcstr++;
  return *(const unsigned char*)pcstr-*(const unsigned char*)npcstr;
}


int ms_ncompare(const char *pcstr,const char *npcstr,size_t n)
{
  while(n--)
   if(*pcstr++!=*npcstr++)
   return *(unsigned char*)(pcstr-1) - *(unsigned char*)(npcstr-1);
  return 0;
}

/*checks if the npcstr string is at the pcstr one*/
char *ms_search( char *pcstr,const char *npcstr)
{
  size_t n = ms_length(npcstr);
  assert(pcstr);
  assert(npcstr);
  
  while(*pcstr)
     if(!ms_ncompare(pcstr++,npcstr,n)){
       return pcstr-1;
        pcstr++;
	 }
  return 0;
}

int main(void){
    char haystack[20] = "TutorialsPoint";
   const char needle[10] = "Point";
   char *ret;

   ret = ms_search(haystack, needle);

   printf("The substring is: %s\n", ret);
   
   return(0);
  
}
