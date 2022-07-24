#include "symtable.h"
#include "intermediate.h"

#define ITEST(x) fprintf(stderr, "INTERMEDIATE(%d)\n", x);

extern void yyerror(char *providedMessage);
extern int yylineno;

const char *iop2string[IOP_NUM] = {
	"ASSIGN", "ADD", "SUB", "MUL", "DIV", "MOD", "AND", "OR", "NOT",
	"IF_EQ", "IF_NOTEQ", "IF_LESSEQ", "IF_GREATEREQ", "IF_LESS", "IF_GREATER",
	"CALL", "PARAM", "RETURN", "GETRETVAL", "FUNCSTART", "FUNCEND",
	"TABLECREATE", "TABLEGETELEM", "TABLESETELEM", "JUMP"
};

/* Returns the string represantation of the given opcode */
const char *iopcode_to_string(IntermediateOpCode op) {
	
	if(op < 0 || op > IOP_NUM) return NULL;
	else return iop2string[op];

}

/* Initializes the intermediate code generation variables */
void intermediate_init() {

	tmp_init();
	loopcounter_init();
	stop_init();

	quads = NULL;
	currQuad = 0;
	total = 0;
	error_flag = 0;

	return;

}

/* Initializes the variables needed to create temporary variables */
void tmp_init() {

	max_tmpnum = MAX_TMP_VARS;
	tmpnum = 0;
	tmpname = malloc(sizeof(char) * max_tmpnum);

	return;

}

/* Initializes loop counter variables */
void loopcounter_init() {

	max_loopcounternum = MAX_LOOPS;
	loopcounternum = 0;
	loopcounter_stack = malloc(sizeof(unsigned int) * max_loopcounternum);

	return;

}

/* Initializes break/continue variables */
void stop_init() {

	break_list = NULL;
	continue_list = NULL;
	return_list = NULL;

	return;

}

/* Backpatching function */
void patchlabel(unsigned int quadNo, unsigned int label) {

	quads[quadNo].label = label;

	return;

}

/* Grows the quad array */
void expand() {

	assert(total == currQuad);
	Quad* p = malloc(NEW_SIZE);
	
	if(quads) {
		memcpy(p, quads, CURR_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;

	return;

}

/* Stores a quad in the quad array */
void emit(IntermediateOpCode op, Expr *arg1, Expr *arg2, Expr *result, 
			unsigned int label) {

	if(currQuad == total) {
		expand();
	}

	Quad* p 	= quads + currQuad++;
	p->op = op;
	p->arg1 	= arg1;
	p->arg2 	= arg2;
	p->result 	= result;
	p->label 	= label;
	p->line	 	= yylineno;

	return;

}

/* Check if the given expression can be a number */
unsigned char check_num(Expr *e) {

	if(e->type == constbool_e || e->type == conststring_e || 
		e->type == nil_e || e->type == newtable_e ||
		e->type == programfunc_e || e->type == libraryfunc_e ||
		e->type == libraryfunc_e || e->type == boolexpr_e) {
		return 0;
	}else {
		return 1;
	}

}

/* Returns an expression representing an arithmetic operation */
Expr *make_arithop(IntermediateOpCode op, Expr *arg1, Expr *arg2) {
	
	if(!check_num(arg1) || !check_num(arg2)) {
		yyerror("error: illegal expression to arithmetic operation");
		return newexpr_constnum(0);
	}else if(arg1->type == constnum_e && arg2->type == constnum_e) {
		if(op == add) return newexpr_constnum(arg1->numConst + arg2->numConst);
		else if(op == sub) return newexpr_constnum(arg1->numConst - arg2->numConst);
		else if(op == mul) return newexpr_constnum(arg1->numConst * arg2->numConst);
		else if(op == divide) {
			if(arg2->numConst == 0) {
				yyerror("error: illegal division by zero");
				return newexpr_constnum(0);
			}else return newexpr_constnum(arg1->numConst / arg2->numConst);
		}else if(op == mod) return newexpr_constnum(((int)arg1->numConst) % ((int)arg2->numConst));
	}else {
		Expr *result = newexpr(arithexpr_e);
		result->sym = newtmp();
		emit(op, arg1, arg2, result, 0);
		return result;
	}

	assert(0);

	/*
	Expr *result = newexpr(arithexpr_e);
	result->sym = newtmp();
	emit(op, arg1, arg2, result, 0);
	return result;
	*/

}

/* Returns the type of the expression if the expression is constant, else returns unknown_e */
ExprType get_typeifconst(Expr *e) {

	if(e->type == constbool_e || e->type == constnum_e || 
		e->type ==conststring_e || e->type == nil_e) {
		return e->type;
	}else {
		return unknown_e;
	}

}

/* Returns an expression representing a constant expression tha derived
   from the 2 arguments, else returns NULL */
Expr *check_ifconstrelop(IntermediateOpCode op, Expr *arg1, Expr *arg2) {

	if(op == if_eq || op == if_noteq) {
		ExprType t1 = get_typeifconst(arg1);
		ExprType t2 = get_typeifconst(arg2);
		if((t1 == constnum_e && t2 == conststring_e)
			|| (t1 == conststring_e && t2 == constnum_e)) {
			yyerror("error: illegal compare between constant string and constant number");
			exit(EXIT_FAILURE);
		}else if(t1 == constnum_e && t2 == constnum_e) {
			if(op == if_eq) return newexpr_constbool(arg1->numConst == arg2->numConst);
			else return newexpr_constbool(arg1->numConst != arg2->numConst);
		}else if(t1 == conststring_e && t2 == conststring_e) {
			if(op == if_eq) return newexpr_constbool(strcmp(arg1->strConst, arg2->strConst) == 0);
			else return newexpr_constbool(strcmp(arg1->strConst, arg2->strConst) != 0);
		}else if(t1 == constbool_e && t2 == constbool_e) {
			if(op == if_eq) return newexpr_constbool(arg1->boolConst == arg2->boolConst);
			else return newexpr_constbool(arg1->boolConst != arg2->boolConst);
		}else if(t1 == constbool_e && t2 == constnum_e) {
			if(op == if_eq) return newexpr_constbool(arg1->boolConst == (arg2->numConst != 0));
			else return newexpr_constbool(arg1->boolConst != (arg2->numConst != 0));
		}else if(t1 == constbool_e && t2 == conststring_e) {
			if(op == if_eq) return newexpr_constbool(arg1->boolConst == (strlen(arg2->strConst) != 0));
			else return newexpr_constbool(arg1->boolConst != (strlen(arg2->strConst) != 0));
		}else if(t1 == constbool_e && t2 == nil_e) {
			if(op == if_eq) return newexpr_constbool(!arg1->boolConst);
			else return newexpr_constbool(arg1->boolConst);
		}else if(t2 == constbool_e && t1 == constnum_e) {
			if(op == if_eq) return newexpr_constbool(arg2->boolConst == (arg1->numConst != 0));
			else return newexpr_constbool(arg2->boolConst != (arg1->numConst != 0));
		}else if(t2 == constbool_e && t1 == conststring_e) {
			if(op == if_eq) return newexpr_constbool(arg2->boolConst == (strlen(arg1->strConst) != 0));
			else return newexpr_constbool(arg2->boolConst != (strlen(arg1->strConst) != 0));
		}else if(t2 == constbool_e && t1 == nil_e) {
			if(op == if_eq) return newexpr_constbool(!arg2->boolConst);
			else return newexpr_constbool(arg2->boolConst);
		}else if(t1 == nil_e && t2 == nil_e) {
			if(op == if_eq) return newexpr_constbool(1);
			else return newexpr_constbool(0);
		}else if((t1 == nil_e && t2 != nil_e && t2 != unknown_e)
					|| (t2 == nil_e && t1 != nil_e && t1 != unknown_e)) {
			if(op == if_eq) return newexpr_constbool(0);
			else return newexpr_constbool(1);
		}else {
			return NULL;
		}
	}else if(!check_num(arg1) || !check_num(arg2)) {
		yyerror("error: illegal expression to relational operation");
		exit(EXIT_FAILURE);
	}else {
		if(arg1->type == constnum_e && arg2->type == constnum_e) {
			if(op == if_greater) return newexpr_constbool(arg1->numConst > arg2->numConst);
			else if(op == if_greatereq) return newexpr_constbool(arg1->numConst >= arg2->numConst);
			else if(op == if_less) return newexpr_constbool(arg1->numConst < arg2->numConst);
			else if(op == if_lesseq) return newexpr_constbool(arg1->numConst <= arg2->numConst);
		}else {
			return NULL;
		}
	}

	assert(0);

}

/* Returns an expression representing a relational operation */
Expr *make_relop(IntermediateOpCode op, Expr *arg1, Expr *arg2) {

	Expr *relop = check_ifconstrelop(op, arg1, arg2);
	if(relop == NULL) {
		Expr *result = newexpr(boolexpr_e);
		result->sym = newtmp();
		emit(op, arg1, arg2, NULL, currQuad + 3);
		emit(assign, newexpr_constbool(0), NULL, result, 0);
		emit(jump, NULL, NULL, NULL, currQuad + 2);
		emit(assign, newexpr_constbool(1), NULL, result, 0);
		return result;
	}else {
		return relop;
	}

	/*
	Expr *result = newexpr(boolexpr_e);
	result->sym = newtmp();
	emit(op, arg1, arg2, NULL, currQuad + 3);
	emit(assign, newexpr_constbool(0), NULL, result, 0);
	emit(jump, NULL, NULL, NULL, currQuad + 2);
	emit(assign, newexpr_constbool(1), NULL, result, 0);
	return result;
	*/

}

/* Returns an expression representing a boolean operation */
Expr *make_boolop(IntermediateOpCode op, Expr *arg1, Expr *arg2) {

	int a1 = -2;
	int a2 = -2;
	int res = 0;

	if(arg1->type == constnum_e) a1 = (arg1->numConst != 0);
	else if(arg1->type == conststring_e) a1 = (strlen(arg1->strConst) != 0);
	else if(arg1->type == constbool_e) a1 = arg1->boolConst;
	else if(arg1->type == newtable_e) a1 = 1;
	else if(arg1->type == programfunc_e || arg1->type == libraryfunc_e) a1 = 1;
	else if(arg1->type == nil_e) a1 = 0;

	if(arg2->type == constnum_e) a2 = (arg2->numConst != 0);
	else if(arg2->type == conststring_e) a2 = (strlen(arg2->strConst) != 0);
	else if(arg2->type == constbool_e) a2 = arg2->boolConst;
	else if(arg2->type == newtable_e) a2 = 1;
	else if(arg2->type == programfunc_e || arg2->type == libraryfunc_e) a2 = 1;
	else if(arg2->type == nil_e) a2 = 0;

	res = a1 + a2;
	if(res >= 0) {
		if(op == and) return newexpr_constbool(res == 2);
		else return newexpr_constbool(res >= 1);
	}else {
		Expr *result = newexpr(boolexpr_e);
		result->sym = newtmp();
		emit(op, arg1, arg2, result, 0);
		return result;
	}

	/*
	Expr *result = newexpr(boolexpr_e);
	result->sym = newtmp();
	emit(op, arg1, arg2, result, 0);
	return result;
	*/

}

/* Returns an expression representing an operation on a single term */
Expr *make_termop(IntermediateOpCode op, Expr *lvalue) {

	Expr *result = newexpr(var_e);
	result->sym = newtmp();

	if(lvalue->type == tableitem_e) {
		Expr *value = make_iftableitem(lvalue);
		emit(assign, value, NULL, result, 0);
		emit(op, value, newexpr_constnum(1), value, 0);
		emit(tablesetelem, lvalue, lvalue->index, value, 0);
	}else {
		emit(assign, lvalue, NULL, result, 0);
		emit(op, lvalue, newexpr_constnum(1), lvalue, 0);
	}

	return result;

}

/* Returns an expression representing an operation on a single term */
Expr *make_opterm(IntermediateOpCode op, Expr *lvalue) {

	if(lvalue->type == tableitem_e) {
		Expr *result = make_iftableitem(lvalue);
		emit(op, result, newexpr_constnum(1), result, 0);
		emit(tablesetelem, lvalue, lvalue->index, result, 0);
		return result;
	}else {
		emit(op, lvalue, newexpr_constnum(1), lvalue, 0);
		Expr *result = newexpr(arithexpr_e);
		result->sym = newtmp();
		emit(assign, lvalue, NULL, result, 0);
		return result;
	}

}

/* Returns an expression representing an assignment */
Expr *make_assign(Expr *lvalue, Expr *e) {

	if(lvalue->type == tableitem_e) {
		emit(tablesetelem, lvalue, lvalue->index, e, 0);
		Expr *assignexpr = make_iftableitem(lvalue);
		assignexpr->type = assignexpr_e;
		return assignexpr;
	}else {
		emit(assign, e, NULL, lvalue, 0);
		Expr *assignexpr = newexpr(assignexpr_e);
		assignexpr->sym = newtmp();
		emit(assign, lvalue, NULL, assignexpr, 0);
		return assignexpr;
	}

}

/* Returns an expression representing a table creation */
Expr *make_table(Expr *elemlist, unsigned char isIndexed) {

	Expr *table = newexpr(newtable_e);
	table->sym = newtmp();
	emit(tablecreate, NULL, NULL, table, 0);
	int i = 0;
	Expr *tmp = elemlist;
	if(tmp != NULL) {
		while(tmp->next != NULL) tmp = tmp->next;
	} 
	while(tmp != NULL) {
		if(isIndexed) {
			emit(tablesetelem, tmp, tmp->index, table, 0);
		}else {
			emit(tablesetelem, newexpr_constnum(i++), tmp, table, 0);
		}
		tmp = tmp->prev;
	}
	return table;

}

/* Returns a lvalue expression */
Expr *make_lvalue_expr(SymbolTableEntry *entry) {

	assert(entry);
	Expr *e = malloc(sizeof(Expr));
	memset(e, 0, sizeof(Expr));

	e->sym = entry;
	e->next = NULL;

	switch(get_primitive_type(entry->type)) {
		case VAR_S:
			e->type = var_e;
			break;
		case PROGRAMFUNC_S:
			e->type = programfunc_e;
			break;
		case LIBRARYFUNC_S:
			e->type = libraryfunc_e;
			break;
		default: assert(0);
	}

	return e;

}

/* Returns an expression representing a table item */
Expr *make_member_item(Expr *lvalue, const char *name) {

	lvalue = make_iftableitem(lvalue);
	Expr *item = newexpr(tableitem_e);
	item->sym = lvalue->sym;
	item->index = newexpr_conststring(name);

	return item;

}

/* Returns an expression representing a table element, else returns the given expression */
Expr *make_iftableitem(Expr* e) {
	
	if(e->type != tableitem_e) {
		return e;
	}else {
		Expr *result = newexpr(var_e);
		result->sym = newtmp();
		emit(tablegetelem, e, e->index, result, 0);
		return result;
	}

}

/* Returns an expression representing a function call */
Expr *make_call(Expr *lvalue, Expr *elist) {

	Expr *func = make_iftableitem(lvalue);
	Expr *tmp = elist;

	while(tmp != NULL) {
		emit(param, NULL, NULL, tmp, 0);
		tmp =  tmp->next;
	}

	emit(call, NULL, NULL, func, 0);
	Expr *result = newexpr(var_e);
	result->sym = newtmp();
	emit(getretval, NULL, NULL, result, 0);

	return result;

}

/* Returns a new exmpty expression */
Expr *newexpr(ExprType type) {

	Expr *e = malloc(sizeof(Expr));
	memset(e, 0, sizeof(Expr));

	e->type = type;
	e->next = NULL;

	return e;

}

/* Returns a constant number expression */
Expr *newexpr_constnum(double num) {

	Expr *e = newexpr(constnum_e);
	e->numConst = num;

	return e;

}

/* Returns a constant string expression */
Expr *newexpr_conststring(const char *str) {

	Expr *e = newexpr(conststring_e);
	e->strConst = strdup(str);

	return e;

}

/* Returns a constant boolean expression */
Expr *newexpr_constbool(unsigned char boolc) {

	Expr *e = newexpr(constbool_e);
	e->boolConst = boolc;

	return e;

}

/* Returns a new temporary variable name */
const char *new_tmp_name() {

	char *tmp = NULL;

	if(snprintf(tmpname, max_tmpnum-1, "_t%d", tmpnum) == max_tmpnum-1) {
		max_tmpnum = max_tmpnum * 2;
		tmp = realloc(tmpname, sizeof(char) * max_tmpnum);
		if(tmp != NULL) {
			tmpname = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	
	tmpnum++;
	
	return tmpname;

}

/* Returns a new temporary variable SymbolTableEntry */
SymbolTableEntry *newtmp() {

	const char *name = new_tmp_name();
	SymbolTableEntry *entry = lookup_on_scope(name, active_scope);
	if(entry == NULL) {
		return insert(name, active_scope, yylineno, TMPVAR, NULL, -1);
	}else {
		return entry;
	}

}

/* Returns 1 if the given name belongs to a temporary variable, else returns 0 */
unsigned int is_tmp_name(const char *str) { 
	
	return *str == '_'; 
	
}

/* Returns 1 if the given expression represents a temporary variable, else returns 0 */
unsigned int is_tmp_expr(Expr *e) {

	if(e->sym) {
		return ((get_primitive_type(e->sym->type) == VAR_S) && is_tmp_name(e->sym->name));
	}else {
		return 0;
	}

}

/* Prints an expression */
void print_expr(FILE *file, Expr *e) {

	if(e != NULL) {
		// print (x)(3 spaces)
		if(e->type == constnum_e) {
			fprintf(file, "%f   ", e->numConst);
		}else if(e->type == conststring_e) {
			fprintf(file, "%s   ", e->strConst);
		}else if(e->type == constbool_e) {
			if(e->boolConst == 1) { // x > 0 may produce wrong result
				fprintf(file, "TRUE   ");
			} else {
				fprintf(file, "FALSE   ");
			}
		}else if(e->type == nil_e){
			fprintf(file, "NIL   ");
		}else {
			fprintf(file, "%s   ", e->sym->name);
		}
	}
	return;

}

/* Prints the quads */
void print_quads(const char *path) {

	int i = 0;
	
	if(error_flag) return;

	FILE *file = fopen(path, "w");
	if(file == NULL) {
		fprintf(stderr, "Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < currQuad; i++) {
		// print (#:)(1 space)(x)(3 spaces)
		fprintf(file, "%d: %s   ", i, iopcode_to_string(quads[i].op));
		print_expr(file, quads[i].arg1);
		print_expr(file, quads[i].arg2);
		print_expr(file, quads[i].result);
		if(quads[i].op != jump) {
			if(quads[i].label != 0) fprintf(file, "%d", quads[i].label);
		}else {
			fprintf(file, "%d", quads[i].label);
		}
		fprintf(file, "\n");
	}

	fclose(file);

	return;
	
}

/* Stores the current loop counter, to the loop counter stack */
void push_loopcounter() {

	if(loopcounternum == max_loopcounternum) {
		max_loopcounternum = max_loopcounternum * 2;
		unsigned int *tmp = realloc(loopcounter_stack, sizeof(unsigned int) * max_loopcounternum);
		if(tmp != NULL) {
			loopcounter_stack = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}

	loopcounter_stack[loopcounternum++] = loopcounter;

	return;
	
}

/* Returns and removes the top value from the loop counter stack */
unsigned int pop_loopcounter() {

	if(loopcounternum == 0) return loopcounter_stack[1];
	else return loopcounter_stack[--loopcounternum];

}

/* Signals an new break/continue in the break/continue list */
void new_stop(StopList **stop_list) {

	StopList *tmp = malloc(sizeof(StopList));
	tmp->flag = 1;
	tmp->next = NULL;

	if(*stop_list == NULL) {
		*stop_list = tmp;
	}else {
		tmp->next = *stop_list;
		*stop_list = tmp;
	}

	return;

}

/* Adds a new break/continue in the break/continue list */
void add_stop(StopList **stop_list) {

	StopList *tmp = malloc(sizeof(StopList));
	tmp->flag = 0;
	tmp->quad_no = currQuad;

	tmp->next = *stop_list;
	*stop_list = tmp;

	return;

}

/* Sets the labels of the active breaks/continues on the break/continue list */
void set_stop_labels(StopList **stop_list, unsigned int label) {

	StopList *tmp = *stop_list;
	while(tmp->flag == 0) {
		patchlabel(tmp->quad_no, label);
		tmp = tmp->next;
	}
	*stop_list = tmp->next;

	return;

}