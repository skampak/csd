#include "symtable.h"
#define STEST(x) fprintf(stderr, "SYMTABLE(%d)\n", x);

//CHECK
/* Jenkins one-at-a-time hash function implementation */
unsigned int shash(const char *key, size_t length) {

  size_t i = 0;
  unsigned int hash = 27;
  
  while (i != length) {
    hash = hash * 31 + key[i] * 33;
    i++;
  }
  hash = hash % SYMTAB_SIZE;
  
  return hash;
  
}

//CHECK
/* Creates a new empty entry */
SymbolTableEntry *newEmptyEntry() {

	SymbolTableEntry *entry = malloc(sizeof(SymbolTableEntry));
	
	entry->isActive = -1;
	entry->type = -1;
	entry->name = NULL;
	entry->scope = -1;
	entry->line = -1;
	entry->args = NULL;
	entry->argc = -1;
	entry->next_on_bucket = NULL;
	entry->next_on_scope = NULL;
	
	return entry;
	
}

//CHECK
/* Initializes the symbol table */
void symbolTableInit() {

	int i = 0;

	funcInit();
	scopeListsInit();
	
	for(i = 0; i < SYMTAB_SIZE; i++) {
		symbol_table[i] = NULL;
	}
	
	insert(PRINT, 0, 0, LIBFUNC, NULL, -1);
	insert(INPUT, 0, 0, LIBFUNC, NULL, -1);
	insert(OBJMEMKEYS, 0, 0, LIBFUNC, NULL, -1);
	insert(OBJTOTMEM, 0, 0, LIBFUNC, NULL, -1);
	insert(OBJCPY, 0, 0, LIBFUNC, NULL, -1);
	insert(TOTARG, 0, 0, LIBFUNC, NULL, -1);
	insert(ARG, 0, 0, LIBFUNC, NULL, -1);
	insert(TYPEOF, 0, 0, LIBFUNC, NULL, -1);
	insert(STRTON, 0, 0, LIBFUNC, NULL, -1);
	insert(SQRT, 0, 0, LIBFUNC, NULL, -1);
	insert(COS, 0, 0, LIBFUNC, NULL, -1);
	insert(SIN, 0, 0, LIBFUNC, NULL, -1);

	return;

}

//CHECK
/* Initializes the scope_lists */
void scopeListsInit() {

	int i = 0;

	/* space allocation: 0 to INIT_SCOPE_DEBTH(including INIT_SCOPE_DEBTH) */
	scope_lists = malloc((INIT_SCOPE_DEBTH + 1) * sizeof(SymbolTableEntry*));
	scope_sentinels = malloc((INIT_SCOPE_DEBTH + 1) * sizeof(SymbolTableEntry*));
	max_scope_depth = INIT_SCOPE_DEBTH;
	scope_depth = 0;
	active_scope = 0;
	funcflag = 0;
	whileflag = 0;
	forflag = 0;
	
	for(i = 0; i <= INIT_SCOPE_DEBTH; i++) { /* INIT_SCOPE_DEBTH(not random number, like 5 or 2) */
		scope_lists[i] = NULL;
		scope_sentinels[i] = NULL;
	}

	return;

}

//CHECK
/* Initializes the variables needed for function actions */
void funcInit() {

	max_funcnum = MAX_UNNAMED_FUNCS;
	funcnum = 0;
	max_funcargc = MAX_NUMBER_OF_ARGUMENTS;
	funcargc = 0;
	funcargs = malloc(sizeof(char*) * max_funcargc);
	funcname = malloc(sizeof(char) * max_funcnum);
	func_entry = NULL;

}

//CHECK
/* Inserts new entry in the symbol table */
SymbolTableEntry *insert(const char *name, unsigned int scope, unsigned int line, 
			SymbolTableType type, char **args, int argc) {
	
	unsigned int position = shash(name, strlen(name));
	SymbolTableEntry *entry = NULL;
	SymbolTableEntry *tmp = NULL;
	int i = 0;
	
	entry = newEmptyEntry();
	entry->isActive = 1;
	entry->type = type;
	entry->name = strdup(name);
	entry->scope = scope;
	entry->line = line;
	
	if(type == USERFUNC) {
		entry->argc = argc;
		entry->args =  malloc(argc * sizeof(char*)); /* char*(not char**) */
		for(i = 0; i < argc; i++) {
			entry->args[i] = strdup(args[i]);
		}
	}
	
	if(symbol_table[position] == NULL) {
		symbol_table[position] = entry;
	} else {
		entry->next_on_bucket = symbol_table[position];
		symbol_table[position] = entry;
	}
	
	if(scope_sentinels[scope] == NULL) {
		scope_sentinels[scope] = entry;
	}
	
	if(scope_lists[scope] == NULL) {
		scope_lists[scope] = entry;
	} else {
		tmp = scope_lists[scope];
		while(tmp->next_on_scope != NULL) {
			tmp = tmp->next_on_scope;
		}
		tmp->next_on_scope = entry;
	}
	
	return entry;
	
}

//CHECK
/* Finds if an entry with the given characteristics exist in 
   any scope on the symbol table and returns it */
SymbolTableEntry *lookup(const char *name) {

	unsigned int position = shash(name, strlen(name));
	SymbolTableEntry *entry = symbol_table[position];
	
	while(entry != NULL) {
		if(strcmp(entry->name, name) == 0 && entry->isActive) return entry;
		entry = entry->next_on_bucket;
	}
	
	return NULL;
	
}

//CHECK
/* Finds if an entry with the given characteristics exist in
   a specific scope on the symbol table and returns it */
SymbolTableEntry *lookup_on_scope(char *name, unsigned int scope) {

	SymbolTableEntry  *entry = scope_sentinels[scope];
	
	while(entry != NULL) {
		if(strcmp(entry->name, name) == 0) return entry;
		entry = entry->next_on_scope;
	}
	
	return NULL;

}

//CHECK
/* Deactivates all the entries of a specific scope in the symbol table */
void hide(unsigned int scope) {

	SymbolTableEntry *entry = scope_sentinels[scope];
	
	while(entry != NULL) {
		entry->isActive = 0;
		entry = entry->next_on_scope;
	}
	
	scope_sentinels[scope] = NULL;
	
	return;

}

/* Prints the entries of the given scope list */
void print_scope_list(int scope) {

	SymbolTableEntry *entry = scope_lists[scope];
	int i = 0;

	while(entry != NULL) {
		if(entry->type == LIBFUNC || entry->type == USERFUNC) {
			printf("FUNCTION:  %s  %d  %d  %d  %s  (", entry->name, entry->scope, 
					entry->line, entry->isActive, strType(entry->type));
			for(i = 0; i < entry->argc; i++) {
				if(i == entry->argc-1) printf("%s", entry->args[i]);
				else printf("%s, ", entry->args[i]);
			}
			printf(")\n");
		} else {
			printf("VARIABLE:  %s  %d  %d  %d  %s\n", entry->name, entry->scope, 
					entry->line, entry->isActive, strType(entry->type));
		}
		entry = entry->next_on_scope;
	}
	
	return;

}

/* Prints the entries of the given bucket */
void print_bucket(SymbolTableEntry *bucket) {

	SymbolTableEntry *entry = bucket;
	int i = 0;

	while(entry != NULL) {
		if(entry->type == LIBFUNC || entry->type == USERFUNC) {
			printf("FUNCTION:  %s  %d  %d  %d  %s  (", entry->name, entry->scope, 
					entry->line, entry->isActive, strType(entry->type));
			for(i = 0; i < entry->argc; i++) {
				if(i == entry->argc-1) printf("%s", entry->args[i]);
				else printf("%s, ", entry->args[i]);
			}
			printf(")\n");
		} else {
			printf("VARIABLE:  %s  %d  %d  %d  %s\n", entry->name, entry->scope, 
					entry->line, entry->isActive, strType(entry->type));
		}
		entry = entry->next_on_bucket;
	}
	
	return;

}

/* Prints the entries of scope lists */
void print_scope_lists() {

	int i = 0;

	printf("====================SCOPE LISTS====================\n");
	printf("|SCOPE (number):                                  |\n");
	printf("|VARIABLE/FUNCTION: name  scope  line  state  type|\n");
	for(i = 0; i <= scope_depth; i++) {
		if(scope_lists[i] != NULL) {
			printf("SCOPE (%d):\n", i);
			print_scope_list(i);
		}
	}
	
}

/* Prints the entries of the symbol table */
void print_symbol_table() {

	int i = 0;

	printf("===================SYMBOL TABLE====================\n");
	printf("|BUCKET (number):                                 |\n");
	printf("|VARIABLE/FUNCTION: name  scope  line  state  type|\n");
	for(i = 0; i < SYMTAB_SIZE; i++) {
		if(symbol_table[i] != NULL) {
			printf("BUCKET (%d):\n", i);
			print_bucket(symbol_table[i]);
		}
	}
	
	return;
	
}

//CHECK
/* Grows the scope lists */
void grow_scope_depth(int new_scope_depth) {

	int i = 0;
	int prev_max_depth = max_scope_depth;
	SymbolTableEntry **tmp = NULL;
	
	while(max_scope_depth < new_scope_depth) {
		max_scope_depth = max_scope_depth * 2;
	}
	
	tmp = realloc(scope_lists, (max_scope_depth + 1) * sizeof(SymbolTableEntry*));
	if(tmp != NULL) {
		scope_lists = tmp;	
	}else {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	tmp = realloc(scope_sentinels, (max_scope_depth + 1) * sizeof(SymbolTableEntry*));
	if(tmp != NULL) {
		scope_sentinels = tmp;	
	}else {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	for(i = prev_max_depth+1; i <= max_scope_depth; i++) {
		scope_lists[i] = NULL;
		scope_sentinels[i] = NULL;
	}
	
	return;
	
}

//CHECK
/* Returns a name for an unnamed function */
char *get_funcname() {

	char *tmp = NULL;

	if(snprintf(funcname, max_funcnum-1, "_f%d", funcnum) == max_funcnum-1) {
		max_funcnum = max_funcnum * 2;
		tmp = realloc(funcname, sizeof(char) * max_funcnum);
		if(tmp != NULL) {
			funcname = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	
	funcnum++;
	
	return funcname;
}

//CHECK
/* Returns true if the given name belongs to a library function else returns false */
int isLibFunc(const char *name) {

	if( (strcmp(name, PRINT) == 0) || (strcmp(name, INPUT) == 0) || 
		(strcmp(name, OBJMEMKEYS) == 0) || (strcmp(name, OBJTOTMEM) == 0) || 
		(strcmp(name, OBJCPY) == 0) || (strcmp(name, TOTARG) == 0) || 
		(strcmp(name, ARG) == 0) || (strcmp(name, TYPEOF) == 0) ||
		(strcmp(name, STRTON) == 0) || (strcmp(name, SQRT) == 0) ||
		(strcmp(name, COS) == 0) || (strcmp(name, SIN) == 0) ) return 1;
	else return 0;

}

//CHECK !!!
/* Returns 1 if variable is accessible else returns 0 */
int isAccessible(SymbolTableEntry *entry) {

	int i = 0;
	
	if(entry->type == USERFUNC) return 1;
	if(entry->scope == 0) return 1;

	for(i = active_scope-1;i >= entry->scope;i--) {
		if(someFuncExists(i)) return 0;
	}
	
	return 1;

}

//CHECK !!!
/* Returns 1 if an intermediate functions exists else returns 0 */
int someFuncExists(int scope) {

	SymbolTableEntry* entry = scope_sentinels[scope];
	
	while(entry != NULL) {
		if(entry->type == USERFUNC) return 1;
		entry = entry->next_on_scope;
	}
	
	return 0;
	
}

//CHECK
/* Returns the appropriate string value of the enum SymbolTableType */
char *strType(SymbolTableType type) {

	switch(type) {
		case VARVAR: return "VARVAR";
		case GLOBALVAR: return "GLOBALVAR";
		case LOCALVAR: return "LOCALVAR";
		case FORMALVAR: return "FORMALVAR";
		case USERFUNC: return "USERFUNC";
		case LIBFUNC: return "LIBFUNC";
		default: 
			assert(0);
	}

}

//CHECK
/* Grows the function arguments table */
void grow_funcargs() {

	char **tmp = NULL;
	max_funcargc = max_funcargc * 2;
	
	tmp = realloc(funcargs, sizeof(char*) * max_funcargc);
	if(tmp != NULL) {
		funcargs = tmp;	
	}else {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	return;

}

//CHECK
/* Reset the variables needed for the function arguments table */
void reset_funcargs() {

	max_funcargc = MAX_NUMBER_OF_ARGUMENTS;
	funcargc = 0;
	funcargs = malloc(sizeof(char*) * max_funcargc);
	func_entry = NULL;
	
	return;

}

/* Frees the space used by the instrumental variables */
void free_ins_vars() {

	free(funcname);
	free(funcargs);

}

