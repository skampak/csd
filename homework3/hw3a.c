#include <stdio.h>
#include <string.h>
int main()
{ int i,j,len,palindrome=1;
  char str[102];
  printf("Enter string to check if it is a palindrome:");
  
  char *remove_newline(char *str)
{
    int len = strlen(str);

    if (len > 0 && str[len-1] == '\n')
        str[len-1] = '\0';          
    if(len>0 && str[len-2]=='\r')
       str[len-2]='\0';
    return str;
}
  fgets(str,sizeof(str),stdin);
  len=strlen(str);
  for(i=0,j=len-2; i<j; i++,j--) {
  
   if (str[i] != str[j]) {palindrome=0; break;}
   if (str[i] == ' ') {++i; continue; }
   if (str[j] == ' ') {--j; continue; }
   
   }
  	if(!palindrome)
  printf("NO");
  	else
  	printf("YES");
  return 0;

}
