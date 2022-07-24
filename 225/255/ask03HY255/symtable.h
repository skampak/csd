#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct SymTable *SymTable_T;


/*returns a new SymTable which is empty*/
SymTable_T   SymTable_new(void);

/*frees the memory that has been allocated from a SymTable,if its null then it returns null*/
void         SymTable_free(SymTable_T oSymTable);

/*returns the number of bindings that occur in the Symtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable);


/*checks if the binding pcKey is already int the SymTable,if it's not it adds it with the pvValue and it returns 1,otherwise Symtable stays the same
   and 0 is returned*/
int          SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);


/* Checks if the pcKey is in the Symtable and removes it,then returns 1 otherwise it returns 0*/
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*Returns 1 if the pckey is invcluded at the SymTable otherwise it returns 0 */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*Returns the value of the pcKey that is included at the Symtable,if it's not invluded it returns NULL*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey);


/* calls the *pfApply function at every binding included at the Symtable with pvExtra as a new parameter for the pfApply function*/
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra);
                   
                   
                   
    
