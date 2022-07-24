#ifndef SYMTABLE_H_
#define SYMTABLE_H_ 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_OFFSETS 10
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

typedef enum ScopeSpaceType {
	PROGRAMVAR,
	FUNCTIONLOCAL,
	FORMALARG
} ScopeSpace;

typedef enum PrimitiveSymType {
	VAR_S,
	PROGRAMFUNC_S,
	LIBRARYFUNC_S
} PrimitiveSymbolType;

typedef enum SymTableType {
	VARVAR, GLOBALVAR, LOCALVAR, TMPVAR,
	FORMALVAR, USERFUNC, LIBFUNC
} SymbolTableType;

typedef struct SymTableEntry {
	int isActive;
	/* Carefull with SymbolTableType and PrimitiveSymbolType
		example: use getPrimitiveType(SymbolTableType type) to get VAR_S, etc */
	SymbolTableType type;
	char *name;
	unsigned int scope;
	unsigned int line;

	/* function vars */
	char **args;
	int argc;
	unsigned int totallocals;
	unsigned int address;

	struct SymTableEntry *next_on_bucket;
	struct SymTableEntry *next_on_scope;

	ScopeSpace space;
	unsigned int offset;
} SymbolTableEntry;

SymbolTableEntry *symbol_table[SYMTAB_SIZE];
SymbolTableEntry **scope_lists;
SymbolTableEntry **scope_sentinels;

unsigned int max_scope_depth; /* max achievable */
unsigned int scope_depth; /* max current */
unsigned int active_scope; /* currently active */
unsigned int infunc_counter;
unsigned char funcflag;
unsigned int funcnum; /* current */
unsigned int max_funcnum; /* max achievable */
char *funcname;
unsigned int funcargc;
unsigned int max_funcargc;
char **funcargs;
SymbolTableEntry *func_entry;
unsigned int programVarOffset;
unsigned int functionLocalOffset;
unsigned int formalArgOffset;
unsigned int scopeSpaceCounter;
unsigned int offsetnum;
unsigned int max_offsetnum;
unsigned int *offset_stack;

/* S hash function implementation */
unsigned int shash(const char *key, size_t length);

/* Creates a new empty entry */
SymbolTableEntry *new_empty_entry();

/* Initializes the symbol table */
void symbol_table_init();

/* Initializes the scope_lists */
void scope_lists_init();

/* Initializes the variables needed for function actions */
void func_init();

/* Initializes the variables needed for scope space actions */
void scope_space_init();

/* Inserts new entry in the symbol table */
SymbolTableEntry *insert(const char *name, unsigned int scope, unsigned int line, 
			SymbolTableType type, char **args, int argc);

/* Finds if an entry with the given characteristics exist in 
   any scope on the symbol table and returns it */
SymbolTableEntry *lookup(const char *name);

/* Finds if an entry with the given characteristics exist in
   a specific scope on the symbol table and returns it */
SymbolTableEntry *lookup_on_scope(const char *name, unsigned int scope);

/* Deactivates all the entries of a specific scope in the symbol table */
void hide(unsigned int scope);

/* Prints the entries of the given scope list */
void print_scope_list(unsigned int scope);

/* Prints the entries of the given bucket */
void print_bucket(SymbolTableEntry *bucket);

/* Prints the entries of scope lists */
void print_scope_lists();

/* Prints the entries of the symbol table */
void print_symbol_table();

/* Grows the scope lists */
void grow_scope_depth(unsigned int new_scope_depth);

/* Returns a name for an unnamed function */
char *get_funcname();

/* Returns true if the given name belongs to a library function else returns false */
unsigned char is_lib_func(const char *name);

/* Returns 1 if variable is accessible else returns 0 */
unsigned char is_accessible(SymbolTableEntry *entry);

/* Returns 1 if an intermediate functions exists else returns 0 */
unsigned char some_func_exists(unsigned int scope);

/* Returns the appropriate string value of the enum SymbolTableType */
const char *strtype(SymbolTableType type);

/* Grows the function arguments table */
void grow_funcargs();

/* Reset the variables needed for the function arguments table */
void reset_funcargs();

/* Returns 1 if the given name belongs to an unnamed function, else returns 0 */
unsigned char is_unnamed_funcname(const char *str);

/* Returns the current scope space */
ScopeSpace get_scope_space();

/* Returns the scope offset of the current scope space */
unsigned int get_scope_offset();

/* Increases the scope offset of the current scope space by 1 */
void inc_scope_offset();

/* Returns the primitive type of the given symbol table entry */
PrimitiveSymbolType get_primitive_type(SymbolTableType type);

/* Sets the scope offset of the current scope space */
void restore_scope_offset(unsigned int num);

/* Stores the current functionLocalOffset to the offset stack */
void push_offset();

/* Returns and removes the top functionLocalOffset from the offset stack */
unsigned int pop_offset();

#endif