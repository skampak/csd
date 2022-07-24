#include<stdio.h> 

int num[10][10],sum[21],r,c,i=0,x; 
void read_N() 
 { for(r=0;r<x;r++) 
  { for(c=0;c<x;c++) 
   { printf("Enter a number[%d][%d] :",r,c); 
     scanf("%d",&num[r][c]); 
   }  
  } 
 } 
void calculate_sum() 
 { int sum_row,sum_col=0,ctr=0; 
   for(r=0;r<x;r++) 
  { sum_row = 0; 
    for(c=0;c<x;c++) 
    { printf("\t%d",num[r][c]); 
      sum_row = sum_row + num[r][c]; 
    } 
sum[ctr] = sum_row; 
ctr++; 
printf(":: %d",sum_row); 
printf("\n"); 
  } 
while(i<x) 
 { printf("\t::"); 
   i++; 
 } 
printf("\n"); 
for(c=0;c<x;c++) 
 {sum_col = 0; 
for(r=0;r<x;r++) 
sum_col = sum_col + num[r][c]; 
sum[ctr] = sum_col; 
ctr++; 
printf("\t%d",sum_col); 
 } 
for(r=0,c=0;r<x;r++,c++) 
sum[2*x] = sum[2*x] + num[r][c]; 
for(r=0,c=x-1;r<x;r++,c--) 
sum[2*x+1] = sum[2*x+1] + num[r][c]; 
 } 
char check_N() 
 { char c; 
   for(i=0;i<2*x+1;i++) 
  { if(sum[i] == sum[i+1]) 
    c = 'Y'; 
    else 
     { c = 'N'; 
       break; 
     } 
  } 
return c; 
 } 
void main() 
{ char c; 

printf("Enter number of rows of the magic square :"); 
scanf("%d",&x); 
read_N(); 
calculate_sum(); 
c = check_N(); 
if(c=='Y') 
printf("\nYES"); 
else 
printf("\nNO"); 
 
}
