#ifndef INTERMEDIATE_H_
#define INTERMEDIATE_H_

#include "symtable.h"

#define MAX_BREAKS 10
#define MAX_LOOPS 10
#define DBL_MAX_10_EXP 10
#define MAX_TMP_VARS 10
#define IOP_NUM 25
#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(Quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(Quad) + CURR_SIZE)

extern int yylineno;

typedef enum IOpCode {
	assign, add, sub,
	mul, divide, mod,
	and, or, not,
	if_eq, if_noteq,
	if_lesseq, if_greatereq, 
	if_less, if_greater, call, 
	param, ret, getretval, 
	funcstart, funcend, 
	tablecreate, tablegetelem, 
	tablesetelem, jump
} IntermediateOpCode;

typedef enum ExpressionType {
	var_e,
	tableitem_e,
	programfunc_e,
	libraryfunc_e,
	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,
	constnum_e,
	constbool_e,
	conststring_e,
	nil_e,
	unknown_e
} ExprType;

typedef struct Expression {
	ExprType 			type;
	SymbolTableEntry 	*sym;
	struct Expression	*index;
	double				numConst;
	char				*strConst;
	unsigned char 		boolConst;
	struct Expression	*next;
	struct Expression	*prev;
} Expr;

typedef struct QuadInfo {
	IntermediateOpCode	op;
	Expr 				*arg1;
	Expr				*arg2;
	Expr 				*result;
	unsigned int 		label;
	unsigned int 		line;
	unsigned int 		taddress;
} Quad;

typedef struct StopList {
	unsigned int quad_no;
	unsigned int flag;
	struct StopList *next;
} StopList;

typedef struct ForprefixObject {
	unsigned int 			test;
	unsigned int			enter;
} ForprefixObj;

typedef struct CallsuffixObject {
	Expr *elist;
	unsigned char method;
	char *name;
} CallsuffixObj;

Quad *quads;
unsigned int currQuad;
unsigned int total;
unsigned int error_flag;

/* tmpvar vars */
unsigned int tmpnum; /* current */
unsigned int max_tmpnum; /* max achievable */
char *tmpname;

/* loopcounter vars */
unsigned int loopcounter;
unsigned int loopcounternum; /* current */
unsigned int max_loopcounternum; /* max achievable */
unsigned int *loopcounter_stack;

StopList *break_list;
StopList *continue_list;
StopList *return_list;

/* Returns the string represantation of the given opcode */
const char *iopcode_to_string(IntermediateOpCode op);

/* Initializes the intermediate code generation variables */
void intermediate_init();

/* Initializes the variables needed to create temporary variables */
void tmp_init();

/* Initializes loop counter variables */
void loopcounter_init();

/* Initializes break/continue variables */
void stop_init();

/* Backpatching function */
void patchlabel(unsigned int quadNo, unsigned int label);

/* Grows the quad array */
void expand();

/* Stores a quad in the quad array */
void emit(IntermediateOpCode op, Expr *arg1, Expr *arg2, Expr *result, 
			unsigned int label);

/* Check if the given expression can be a number */
unsigned char check_num(Expr *e);

/* Returns an expression representing an arithmetic operation */
Expr *make_arithop(IntermediateOpCode op, Expr *arg1, Expr *arg2);

/* Returns the type of the expression if the expression is constant, else returns unknown_e */
ExprType get_typeifconst(Expr *e);

/* Returns an expression representing a constant expression tha derived
   from the 2 arguments, else returns NULL */
Expr *check_ifconstrelop(IntermediateOpCode op, Expr *arg1, Expr *arg2);

/* Returns an expression representing a relational operation */
Expr *make_relop(IntermediateOpCode op, Expr *arg1, Expr *arg2);

/* Returns an expression representing a boolean operation */
Expr *make_boolop(IntermediateOpCode op, Expr *arg1, Expr *arg2);

/* Returns an expression representing an operation on a single term */
Expr *make_termop(IntermediateOpCode op, Expr *lvalue);

/* Returns an expression representing an operation on a single term */
Expr *make_opterm(IntermediateOpCode op, Expr *lvalue);

/* Returns an expression representing an assignment */
Expr *make_assign(Expr *lvalue, Expr *e);

/* Returns an expression representing a table creation */
Expr *make_table(Expr *elemlist, unsigned char isIndexed);

/* Returns a lvalue expression */
Expr *make_lvalue_expr(SymbolTableEntry *entry);

/* Returns an expression representing a table item */
Expr *make_member_item(Expr *lvalue, const char *name);

/* Returns an expression representing a table element, else returns the given expression */
Expr *make_iftableitem(Expr *e);

/* Returns an expression representing a function call */
Expr *make_call(Expr *lvalue, Expr *elist);

/* Returns a new exmpty expression */
Expr *newexpr(ExprType type);

/* Returns a constant number expression */
Expr *newexpr_constnum(double num);

/* Returns a constant string expression */
Expr *newexpr_conststring(const char *str);

/* Returns a constant boolean expression */
Expr *newexpr_constbool(unsigned char boolc);

/* Returns a new temporary variable name */
const char *new_tmp_name();

/* Returns a new temporary variable SymbolTableEntry */
SymbolTableEntry *newtmp();

/* Returns 1 if the given name belongs to a temporary variable, else returns 0 */
unsigned int is_tmp_name(const char *str);

/* Returns 1 if the given expression represents a temporary variable, else returns 0 */
unsigned int is_tmp_expr(Expr *e);

/* Prints an expression */
void print_expr(FILE *file, Expr *e);

/* Prints the quads */
void print_quads(const char *path);

/* Stores the current loop counter, to the loop counter stack */
void push_loopcounter();

/* Returns and removes the top value from the loop counter stack */
unsigned int pop_loopcounter();

/* Signals an new break/continue in the break/continue list */
void new_stop(StopList **stop_list);

/* Adds a new break/continue in the break/continue list */
void add_stop(StopList **stop_list);

/* Sets the labels of the active breaks/continues on the break/continue list */
void set_stop_labels(StopList **stop_list, unsigned int label);

#endif