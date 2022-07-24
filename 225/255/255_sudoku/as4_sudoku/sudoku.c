
#include "sudoku.h"




Grid_T sudoku_read(void){
    Grid_T tmp;
    int m,g,s,cnt=0;
    for(g=0; g<10;g++){
        for(s=0;s<10; s++){
            scanf("%d",&m);
            grid_update_value(&tmp,g,s,m);
            cnt++;
        }
    }
   return tmp;
}

void sudoku_print(FILE *s, Grid_T g)
{
  int i,j,value;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      value=grid_read_value(g,i,j);
      fprintf(s,"%d ",value);
      j++;
    }
    j=0;
    i++;
  }
}

Grid_T sudoku_generate(int nelts, int unique)
{
  Grid_T newsud;
  int i,j,n;
  n=81;
  while(n!=nelts)
  {
    i=rand()%9;
    j=rand()%9;
    grid_update_value(&newsud,i,j,0);
    n--;
  }
  return newsud;
}
