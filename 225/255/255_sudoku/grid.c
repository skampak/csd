#include <stdio.h>
#include "grid.h"



void grid_update_value(Grid_T *g, int i, int j, int n){
     if(n<10 && n>0) 
         g->elts[i][j].val=n;
     else
    	return;
}

int grid_read_value(Grid_T g, int i, int j){
    int value;
    if(j>0 && j<10 && i>0 && i<10)
    	 value=g.elts[i][j].val;         

     	exit(0);
    return value;
}

void grid_set_choice(Grid_T *g, int i, int j, int n){
   if(n<10 && n>0)
    	if(j>0 && j<10 && i>0 && i<10)
       	    g->elts[i][j].choices.num[n]==1;
        else
            return;
   else
       return;

}

void grid_clear_choice(Grid_T *g, int i, int j, int n) {
    if(n<10 && n>0)
        if(j>0 && j<10 && i>0 && i<10)
            g->elts[i][j].choices.num[n]==0;
        else
            return;
    else
        return;
}

int grid_choice_is_valid(Grid_T g, int i, int j, int n){
    if(n<10 && n>0)
        if(j>0 && j<10 && i<10 && i>0)
             valid=g->elts[i][j].choices.num[n];
    return value;
}

void grid_remove_choice(Grid_T *g, int i, int j, int n){
 assert(g);
  if(n>0 && n<10)
    if(j>0 && j<10 && i<10 && i>0)
      g->elts[i][j].choices.num[n]=0;
      g->elts[i][j].choices.count--;
  else
    return;
}

int read_unique(Grid_T g){
    return g.unique;
}
