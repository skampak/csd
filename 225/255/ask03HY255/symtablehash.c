#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "symtable.h"
 

#define HASH_MULTIPLIER 65599
#define BUCKETS 509

struct stnode{
	const char *key;
	const void *value;
	struct stnode *next;
};


struct SymTable{
	unsigned int totalbinds;
	struct stnode *A[BUCKETS];
};

/*HUSH FUNCTION*/
static unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  return uiHash;
} 

/*returns a new SymTable which is empty*/
SymTable_T   SymTable_new(void){
	SymTable_T newhsymtab;
	unsigned int i;
	newhsymtab=malloc(sizeof(struct SymTable));
	if (newhsymtab == NULL)
  {
  	printf("memory can not be allocated for the new symbol table");
  	return NULL;
  }
	for(i=0U;i<BUCKETS;i++){
		newhsymtab->A[i]=NULL;
    }
	newhsymtab->totalbinds=0U;
	return newhsymtab;
}

/*frees the memory that has been allocated from a SymTable,if its null then it returns null*/
void         SymTable_free(SymTable_T oSymTable){
	int i;
	assert(oSymTable);
	
	for(i=0;i<BUCKETS;i++){
		if(oSymTable->A[i]!=NULL){
		
		free(oSymTable->A[i]->key);
		
	}
	}
	
	free(oSymTable);
}

/*returns the number of bindings that occur in the Symtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable);
	return oSymTable->totalbinds;
}

/*checks if the binding pcKey is already int the SymTable,if it's not it adds it with the pvValue and it returns 1,otherwise Symtable stays the same
   and 0 is returned*/
int          SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
	struct stnode *tmp;
	unsigned int k;
	assert(oSymTable);
	assert(pcKey);
	
	tmp=malloc(sizeof(struct stnode));
	if(SymTable_contains(oSymTable,pcKey)==1){
		return 0;
	}else{
	 struct stnode *tmp=malloc(sizeof(struct stnode));
	tmp->key = (const char*)malloc(strlen(pcKey) + 1);
	strcpy(tmp->key,pcKey);
	tmp->value=pvValue;
	k=SymTable_hash(pcKey);
	oSymTable->A[k]=tmp;
	oSymTable->totalbinds++;
	
	return 1;
	}
}


/* Checks if the pcKey is in the Symtable and removes it,then returns 1 otherwise it returns 0*/
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	unsigned int k;
	assert(oSymTable);
	assert(pcKey);
	
	k=SymTable_hash(pcKey);
	if(SymTable_contains(oSymTable,pcKey)==0){
		return 0;
	}else{
		free(oSymTable->A[k]);
		oSymTable->A[k]=NULL;
		oSymTable->totalbinds--;
		return 1;
	}
}

/*Returns 1 if the pckey is invcluded at the SymTable otherwise it returns 0 */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	unsigned int k;
	assert(oSymTable);
	assert(pcKey);
	
	k=SymTable_hash(pcKey);
	
	if(oSymTable->A[k]!=NULL){
		return 1;
	}else{
		return 0;
	}
}

/*Returns the value of the pcKey that is included at the Symtable,if it's not invluded it returns NULL*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
	unsigned int k;
	assert(oSymTable);
	assert(pcKey);
	
	k=SymTable_hash(pcKey);
	if(SymTable_contains(oSymTable,pcKey)==0){
		return 0;
	}else{
		return (void *)oSymTable->A[k]->value;
	}
}

/* calls the *pfApply function at every binding included at the Symtable with pvExtra as a new parameter for the pfApply function*/
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra)
				   
	{
    unsigned int i;
    struct stnode *tmp;
	assert(oSymTable);
	assert(pfApply);
	

	for(i=0U;i<BUCKETS;i++){
	
	    tmp=oSymTable->A[i];
	    if(tmp!=NULL)
		pfApply(tmp->key, &(tmp->value), (void *)pvExtra);

	}
}

	
	
			   
				   
				   
				   
				   
                   


