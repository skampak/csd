#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define SYMTAB_SIZE 1024
#define INIT_SCOPE_DEBTH 20
#define MAX_UNNAMED_FUNCS 10
#define MAX_NUMBER_OF_ARGUMENTS 3
#define PRINT 		"print"
#define INPUT 		"input"
#define OBJMEMKEYS 	"objectmemberkeys"
#define OBJTOTMEM 	"objecttotalmembers"
#define OBJCPY 		"objectcopy"
#define TOTARG 		"totalarguments"
#define ARG 		"argument"
#define TYPEOF 		"typeof"
#define STRTON 		"strtonum"
#define SQRT 		"sqrt"
#define COS			"cos"
#define SIN			"sin"

typedef enum SymTableType {
	VARVAR, GLOBALVAR, LOCALVAR,
	FORMALVAR, USERFUNC, LIBFUNC
} SymbolTableType;

typedef struct SymTableEntry {
	int isActive;
	SymbolTableType type;
	char *name;
	unsigned int scope;
	unsigned int line;
	char **args;
	int argc;
	struct SymTableEntry *next_on_bucket;
	struct SymTableEntry *next_on_scope;
} SymbolTableEntry;

SymbolTableEntry *symbol_table[SYMTAB_SIZE];
SymbolTableEntry **scope_lists;
SymbolTableEntry **scope_sentinels;

int max_scope_depth; /* max achievable */
int scope_depth; /* max current */
int active_scope; /* currently active */
int funcflag;
int whileflag;
int forflag;
int funcnum; /* current */
int max_funcnum; /* max achievable */
char *funcname;
int funcargc;
int max_funcargc;
char **funcargs;
SymbolTableEntry *func_entry;

/* Jenkins one-at-a-time hash function implementation */
unsigned int shash(const char *key, size_t length);

/* Creates a new empty entry */
SymbolTableEntry* newEmptyEntry();

/* Initializes the symbol table */
void symbolTableInit();

/* Initializes the scope_lists */
void scopeListsInit();

/* Initializes the variables needed for function actions */
void funcInit();

/* Inserts new entry in the symbol table */
SymbolTableEntry *insert(const char *name, unsigned int scope, unsigned int line, 
			SymbolTableType type, char **args, int argc);

/* Finds if an entry with the given characteristics exist in 
   any scope on the symbol table */
SymbolTableEntry *lookup(const char *name);

/* Finds if an entry with the given characteristics exist in
   a specific scope on the symbol table */
SymbolTableEntry *lookup_on_scope(char *name, unsigned int scope);

/* Deactivates all the entries of a specific scope in the symbol table */
void hide(unsigned int scope);

/* Prints the entries of the given scope list */
void print_scope_list(int scope);

/* Prints the entries of the given bucket */
void print_bucket(SymbolTableEntry *bucket);

/* Prints the entries of scope */
void print_scope_lists();

/* Prints the entries of the symbol table */
void print_symbol_table();

/* Grows the scope lists */
void grow_scope_depth(int scope);

/* Returns a name for an unnamed function */
char *get_funcname();

/* Returns 1 if the given name belongs to a library function else returns 0 */
int isLibFunc(const char *name);

/* Returns 1 if variable is accessible else returns 0 */
int isAccessible(SymbolTableEntry *entry);

/* Returns 1 if an intermediate functions exists else returns 0 */
int someFuncExists(int scope);

/* Returns the appropriate string value of the enum SymbolTableType */
char *strType(SymbolTableType type);

/* Grows the argument table */
void grow_funcargs();

/* Reset the variables needed for the function arguments table */
void reset_funcargs();

/* Frees the space used by the instrumental variables */
void free_ins_vars();
