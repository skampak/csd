#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"


void pfApply(const char *pcKey, void *pvValue, void *pvExtra){
   *(int *)pvValue += *(int *)pvExtra;
    
}

int main(void)
{
  SymTable_T oSymTable;
  
  const char test[] = "SofiaKampaki";
  char K[2];
  int v[]  = {8,3,30,3,20,16,456,77,123,4,8,1995};
  int i,pvExtra;
  int s=sizeof(test);
  oSymTable = SymTable_new();
  K[1] = '\0';  

/****************test put*************/
  for(i = 0; i < s-1; i++)
  {
    K[0]=test[i];
    printf("Key  %s with value %d is in the SymTable if x=1,x is %d\n" ,K,v[i],SymTable_put(oSymTable, K, (int*)v[i]));
  }
  /***************test length**********/
   printf("Symbol Table length is %u \n" , SymTable_getLength(oSymTable));
   
  
  /***************test contains********/
  for(i = 0; i < s-1; i++)
  {
    K[0]=test[i];
    if((int)SymTable_contains(oSymTable,K)==1)
      printf("Key %s is in the Symbol Table\n",K);
    else
      printf("Key %s is NOT in the Symbol Table\n\n",K);      
  }  
  printf("\n");
  
  /**************test remove***********/
  printf("Remove key %s from the Symbol Table if x=1 it has been removed,x is %d\n","a",SymTable_remove(oSymTable, "a"));  /*in this example a is removed*/
   printf("Symbol Table length is %u \n" , SymTable_getLength(oSymTable));   /*the length should be 1 number less*/
   
   /************test  get*************/
  for(i = 0; i < s-1; i++)
  {
    K[0]=test[i];
    if(SymTable_get(oSymTable,K) != NULL)
      printf("Key %s has value %d\n",K,(int)SymTable_get(oSymTable,K));
  }  
  printf("\n");
  
  
  /************test map**************/
  pvExtra=5;     /*5 is added to the value of each key*/
  SymTable_map(oSymTable, &pfApply, &pvExtra);
  
  
  for(i = 0; i < s-1; i++)                           /*we run again the test for the get function to see if the map works*/
  {
    K[0]=test[i];
    if(SymTable_get(oSymTable,K) != NULL)
      printf("Key %s has value %d\n",K,(int)SymTable_get(oSymTable,K));
  }  
  printf("\n");
  
  SymTable_free(oSymTable);
  return 0;
}
