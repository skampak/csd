#include "symtable.h"


/*Struct that refers to each binding at the SymbolTable aka each node for the linked list*/
typedef struct pair{
	
	const char *key;
	const void *value;
	struct pair *next;
} stnode;

/*Struct that refers to the Symtable. Totalbind is the number of bindings at the symtable and the head is the first node at the list*/
struct SymTable{
	unsigned int totalbind;
	struct stnode *head;
};

/*Implementation of the functions from the .h file*/

/*returns a new SymTable which is empty*/
SymTable_T SymTable_new(void)
{
  SymTable_T newsymtab;
  newsymtab =(SymTable_T)malloc(sizeof(struct SymTable));
  if (newsymtab == NULL)
  {
  	printf("memory can not be allocated for the new symbol table");
  	return NULL;
  }
  newsymtab->totalbind=0;
  newsymtab->head=NULL;
  return newsymtab;
}


/*frees the memory that has been allocated from a SymTable,if its null then it returns null*/
void  SymTable_free(SymTable_T oSymTable){
  stnode *headnode=oSymTable->head;
  stnode *nextnode;
  assert(oSymTable!=NULL);

  for(headnode;headnode!=NULL;headnode=nextnode){
  	nextnode=headnode->next;
  	free(headnode->key);
  	free(headnode);
  }
  free(oSymTable);
 }
 
/*returns the number of bindings that occur in the Symtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable);
	return oSymTable->totalbind;
}

/*checks if the binding pcKey is already int the SymTable,if it's not it adds it with the pvValue and it returns 1,otherwise Symtable stays the same
   and 0 is returned*/
int          SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
	assert(oSymTable);
	assert(pcKey);
	assert(pvValue);
	
	if(SymTable_contains(oSymTable,pcKey)){
		return 0;
	}else{
	
	
	
	stnode *newnode=malloc(sizeof(stnode));
	newnode->key = (const char*)malloc(strlen(pcKey) + 1);
	strcpy(newnode->key,pcKey);
	newnode->value=pvValue;
	newnode->next=oSymTable->head;
	oSymTable->head=newnode;
	oSymTable->totalbind++;

	return 1;
}
}

/* Checks if the pcKey is in the Symtable and removes it,then returns 1 otherwise it returns 0*/
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	stnode *prev;
	stnode *nextnode;
	assert(oSymTable);
	assert(pcKey);
	
	
	if(SymTable_contains(oSymTable,pcKey)){
		oSymTable->totalbind--;
		nextnode=oSymTable->head;
		prev=nextnode;
		while(nextnode!=NULL){
		
		if(strcmp(nextnode->key,pcKey)==0){
			
			if(nextnode==prev){
				oSymTable->head=nextnode->next;   /*the pckey is at the head node*/
			}else{
				prev->next=nextnode->next;
				free(nextnode->key);
				free(nextnode);
				return 1;
			}
		}else{
				prev=nextnode;
				nextnode=nextnode->next;
		}
		}
	}
		return 0;
}

	
/*Returns 1 if the pckey is invcluded at the SymTable otherwise it returns 0 */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	stnode *tmp;
	tmp=oSymTable->head;
	assert(oSymTable);
	assert(pcKey);
	
	while(tmp!=NULL){
		if(strcmp(tmp->key,pcKey)==0){
			return 1;
		}else{
			tmp=tmp->next;
		}
		
	}
	return 0;
}
	
	
/*Returns the value of the pcKey that is included at the Symtable,if it's not included it returns NULL*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
	stnode *tmp;
	tmp=oSymTable->head;
	assert(oSymTable);
	assert(pcKey);
	
	if(SymTable_contains(oSymTable,pcKey)){
			while(tmp!=NULL){
			
			if(strcmp(tmp->key,pcKey)==0){
			
			return tmp->value;
		}else{
			tmp=tmp->next;
		}
	}
	}else{
	   return NULL;

	}
}

/* calls the *pfApply function at every binding included at the Symtable with pvExtra as a new parameter for the pfApply function*/
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra)
{
	stnode *tmp;
	tmp=oSymTable->head;
	assert(oSymTable);
	assert(pfApply);
	
	while(tmp!=NULL){
		pfApply(tmp->key, &(tmp->value), (void *)pvExtra);
		
    tmp=tmp->next;
	}
	
}


   
 
    





