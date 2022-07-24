#include "target.h"

#define TTEST(x) fprintf(stderr, "TARGET(%d)\n", x);

char *vmop2string[TOP_NUM] = {
	"ASSIGN", "ADD", "SUB", "MUL", "DIV", "MOD", "AND", "OR", "NOT",
	"JEQ", "JNE", "JLE", "JGE", "JLT", "JGT", "CALL", "PUSHARG", "FUNCENTER", 
	"FUNCEXIT", "NEWTABLE", "TABLEGETELEM", "TABLESETELEM", "JUMP", "NOP"
};

generator_func_t generators[] = {
		generate_ASSIGN,
		generate_ADD, 
		generate_SUB, 
		generate_MUL, 
		generate_DIV, 
		generate_MOD,
		generate_AND,
		generate_OR, 
		generate_NOT,
		generate_IF_EQ, 
		generate_IF_NOTEQ, 
		generate_IF_LESSEQ,
		generate_IF_GREATEREQ, 
		generate_IF_LESS, 
		generate_IF_GREATER,
		generate_CALL, 
		generate_PARAM,
		generate_RETURN, 
		generate_GETRETVAL, 
		generate_FUNCSTART, 
		generate_FUNCEND,
		generate_NEWTABLE, 
		generate_TABLEGETELM, 
		generate_TABLESETELEM, 
		generate_JUMP,
		generate_NOP
	};

/* Returns the string represantation of the given opcode */
char* vmopcode_to_string(IntermediateOpCode op) {
	
	if(op < 0 || op > TOP_NUM) return NULL;
	else return vmop2string[op];

}

/* Returns a new empty instruction */
Instruction new_instr() {

	Instruction instr;
	instr.opcode = nop_v;
	instr.arg1.type = omit_a;
	instr.arg1.val = 0;
	instr.arg2.type = omit_a;
	instr.arg2.val = 0;
	instr.result.type = omit_a;
	instr.result.val = 0;
	instr.srcLine = 0;

	return instr;

}

/* Initializes the target code generation variables */
void target_init() {

	ijump_init();
	nsul_init();

	instructions = NULL;
	currInstr = 0;
	totalInstr = 0;
	currprocessedquad = 0;

	return;

}

/* Initializes the incomplete jump variables */
void ijump_init() {

	ij_head = NULL; 
	ij_total = 0;

	return;

}

/* Initializes the variables needed to store
   n : constant numbers
   s : constant numbers
   u : user functions
   l : library functions */
void nsul_init() {

	maxNumConsts = MAX_NUMCONSTS;
	totalNumConsts = 0;
	numConsts = malloc(sizeof(double) * maxNumConsts);

	maxStringConsts = MAX_STRINGCONSTS;
	totalStringConsts = 0;
	stringConsts = malloc(sizeof(char*) * maxStringConsts);

	maxUserFuncs = MAX_USERFUNCS;
	totalUserFuncs = 0;
	userFuncs = malloc(sizeof(UserFunc) * maxUserFuncs);

	totalNamedLibfuncs = 0;
	namedLibfuncs = malloc(sizeof(char*) * MAX_NAMEDLIBFUNCS);

	return;

}

/* Inserts a jump in the incomplete jump list */
void add_incomplete_jump(unsigned instrNo, unsigned iaddress) {

	IncompleteJump *tmp = malloc(sizeof(IncompleteJump));
	tmp->instrNo = instrNo;
	tmp->iaddress = iaddress;
	tmp->next = NULL;
	
	if(ij_head == NULL) {
		ij_head = tmp;
	} else {
		tmp->next = ij_head;
		ij_head = tmp;
	}

	return;

}

/* Patches incomplete jumps */
void patch_incomplete_jump() {

	IncompleteJump *tmp = ij_head;
	while(tmp != NULL) {
		if(tmp->iaddress == currQuad) {
			instructions[tmp->instrNo].result.val = currInstr;
		}else {
			instructions[tmp->instrNo].result.val = quads[tmp->iaddress].taddress;
		}
		tmp = tmp->next;
	}

	return;

}

/* Grows the instruction array */
void expand_instr() {

	assert(totalInstr == currInstr);
	Instruction *p = malloc(NEW_INSTR_SIZE);
	
	if(instructions) {
		memcpy(p, instructions, CURR_INSTR_SIZE);
		free(instructions);
	}
	instructions = p;
	totalInstr += EXPAND_INSTR_SIZE;

	return;

}

/* Stores an isntruction in the instruction array */
void emit_instr(Instruction t) {

	if(currInstr == totalInstr) {
		expand_instr();
	}

	Instruction *p 	= instructions + currInstr++;
	p->opcode   	= t.opcode;
	p->arg1 		= t.arg1;
	p->arg2 		= t.arg2;
	p->result 		= t.result;
	p->srcLine		= t.srcLine;

	return;

}

/* Produces an operand */
void make_operand(Expr *e, VMarg *arg) {
	
	switch(e->type) {
		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case assignexpr_e:
		case newtable_e:
			assert(e->sym);
			arg->val = e->sym->offset;
			switch(e->sym->space) {
				case PROGRAMVAR: 
					arg->type = global_a;
					break;
				case FUNCTIONLOCAL: 
					arg->type = local_a;
					break;
				case FORMALARG:
					arg->type = formal_a; 
					break;
				default:
					assert(0);
			}
			break;
		case constbool_e: 
			arg->val = e->boolConst;
			arg->type = bool_a;
			break;
		case conststring_e:
			arg->val = consts_newstring(e->strConst);
			arg->type = string_a;
			break;
		case constnum_e:
			arg->val = consts_newnumber(e->numConst);
			arg->type = number_a;
			break;
		case nil_e:
			arg->type = nil_a;
			break;
		case programfunc_e:
			arg->type = userfunc_a;
			arg->val = userfuncs_newfunc(e->sym);
			break;
		case libraryfunc_e:
			arg->type = libfunc_a;
			arg->val = libfuncs_newused(e->sym->name);
			break;
		default:
			assert(0);
	}

	return;

}

/* Produces numbers for generated instructions */
void make_numberoperand(VMarg *arg, double val) {

	arg->val = consts_newnumber(val);
	arg->type = number_a;

	return;

}

/* Produces booleans for generated instructions */
void make_booloperand(VMarg *arg, unsigned char val) {

	arg->val = val;
	arg->type = bool_a;

	return;

}

/* Produces return values for generated instructions */
void make_retvaloperand(VMarg *arg) {

	arg->type = retval_a;

	return;

}

/* Produces omit values for generated instructions */
void reset_operand(VMarg *arg) {

	arg->type = omit_a;

	return;

}

/* Generates an instruction */
void generate(VirtualMachineOpCode op, Quad *quad) {
	
	Instruction t = new_instr();
	t.opcode = op;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);
	make_operand(quad->result, &t.result);
	quad->taddress = currInstr;
	emit_instr(t);

	return;
	
} 

/* Generates a relational instruction */
void generate_relational(VirtualMachineOpCode op, Quad *quad) {

	Instruction t = new_instr();
	t.opcode = op;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);

	t.result.type = label_a;
	if(quad->label < currprocessedquad) {
		t.result.val = quads[quad->label].taddress;
	}else {
		add_incomplete_jump(currInstr, quad->label);
	}
	quad->taddress = currInstr;
	emit_instr(t);

	return;

} 

/* Generates an assign instruction */
void generate_ASSIGN(Quad *quad) {

	Instruction t = new_instr();
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->result, &t.result);
	quad->taddress = currInstr;
	emit_instr(t);

	return;

} 

/* Generates an add instruction */
void generate_ADD(Quad *quad) {

	return generate(add_v, quad);

} 

/* Generates a sub instruction */
void generate_SUB(Quad *quad) {

	return generate(sub_v, quad);

}
 
 /* Generates a mul instruction */
void generate_MUL(Quad *quad) {

	return generate(mul_v, quad);

} 

/* Generates a div instruction */
void generate_DIV(Quad *quad) {

	return generate(div_v, quad);

} 

/* Generates a mod instruction */
void generate_MOD(Quad *quad) {

	return generate(mod_v, quad);

}

/* Generates a newtable instruction */
void generate_NEWTABLE(Quad *quad) {

	Instruction t = new_instr();
	t.opcode = newtable_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.result);
	quad->taddress = currInstr;
	emit_instr(t);

	return;

} 

/* Generates a tablegetelem instruction */
void generate_TABLEGETELM(Quad *quad) {

	return generate(tablegetelem_v, quad);

}

/* Generates a tablesetelem instruction */
void generate_TABLESETELEM(Quad *quad) {

	return generate(tablesetelem_v, quad); 

}

/* Generates a nop instruction */
void generate_NOP(Quad *quad) {

	Instruction t = new_instr(); 
	t.opcode = nop_v;
	t.srcLine = quad->line;
	emit_instr(t);

	return;

} 

/* Generates a jump instruction */
void generate_JUMP(Quad *quad) {

	return generate_relational(jump_v, quad);

} 

/* Generates an if_eq instruction */
void generate_IF_EQ(Quad *quad) {

	return generate_relational(jeq_v, quad);

} 

/* Generates an if_noteq instruction */
void generate_IF_NOTEQ(Quad *quad) {

	return generate_relational(jne_v, quad);

} 

/* Generates an if_lesseq instruction */
void generate_IF_LESSEQ(Quad *quad) {

	return generate_relational(jle_v, quad);

} 

/* Generates an if_greatereq instruction */
void generate_IF_GREATEREQ(Quad *quad) {

	return generate_relational(jge_v, quad);

} 

/* Generates an if_less instruction */
void generate_IF_LESS(Quad *quad) {

	return generate_relational(jlt_v, quad);

} 

/* Generates an if_greater instruction */
void generate_IF_GREATER(Quad *quad) {

	return generate_relational(jgt_v, quad);

}

/* Generates a not instruction */
void generate_NOT(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr();
	
	t.opcode = jeq_v;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_booloperand(&t.arg2, 0);
	t.result.type = label_a;
	t.result.val = currInstr + 3;
	emit_instr(t);
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 0);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t); 
	
	t.opcode = jump_v;
	t.srcLine = quad->line;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = currInstr + 2;
	emit_instr(t);
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 1);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

}

/* Generates an and instruction */ /* 444 */
void generate_AND(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr(); 
	
	t.opcode = jeq_v;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_booloperand(&t.arg2, 0);
	t.result.type = label_a;
	t.result.val = currInstr + 4;
	emit_instr(t); 
	
	make_operand(quad->arg2, &t.arg1);
	t.result.val = currInstr + 3;
	emit_instr(t); 
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 1);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t);
	
	t.opcode = jump_v;
	t.srcLine = quad->line;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = currInstr + 2;
	emit_instr(t);
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 0);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

} 

/* Generates an or instruction */ /* 444 */
void generate_OR(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr(); 
	
	t.opcode = jeq_v;
	t.srcLine = quad->line;
	make_operand(quad->arg1, &t.arg1);
	make_booloperand(&t.arg2, 1);
	t.result.type = label_a;
	t.result.val = currInstr + 4;
	emit_instr(t); 
	
	make_operand(quad->arg2, &t.arg1);
	t.result.val = currInstr + 3;
	emit_instr(t); 
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 0);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t);
	
	t.opcode = jump_v;
	t.srcLine = quad->line;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = currInstr + 2;
	emit_instr(t);
	
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_booloperand(&t.arg1, 1);
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

}

/* Generates a param istruction */
void generate_PARAM(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = pusharg_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

}

/* Generates a call instruction */
void generate_CALL(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = call_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

}

/* Generates a call instruction */
void generate_GETRETVAL(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.arg1);
	make_retvaloperand(&t.result);
	emit_instr(t);

	return;

} 

/* Generates a funcstart instruction */
void generate_FUNCSTART(Quad *quad) {

	SymbolTableEntry *f = quad->result->sym;
	f->address = currInstr;
	userfuncs_newfunc(f);
	
	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = funcenter_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

}

/* Generates a funcend instruction */
void generate_FUNCEND(Quad *quad) {
	
	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = funcexit_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.result);
	emit_instr(t);

	return;

} 

/* Generates a return instruction */
void generate_RETURN(Quad *quad) {

	quad->taddress = currInstr;
	Instruction t = new_instr();
	t.opcode = assign_v;
	t.srcLine = quad->line;
	make_operand(quad->result, &t.arg1);
	make_retvaloperand(&t.result);
	emit_instr(t);

	return;

} 

/* Calls a generator for each quad */
void generate_instructions() {

	for (currprocessedquad = 0; currprocessedquad < currQuad; currprocessedquad++) {
		(*generators[quads[currprocessedquad].op])(quads + currprocessedquad); 
	}

	patch_incomplete_jump();

	return;

}

/* Returns the position of a constant number in the constant numbers array,
   if it doesnt exist it is inserted */
unsigned int consts_newnumber(double n) {

	int i = 0;
	
	for(i = 0; i < totalNumConsts; i++) {
		if(n == numConsts[i]) return i;
	}
	
	if(totalNumConsts == maxNumConsts) {
		maxNumConsts = maxNumConsts * 2;
		double *tmp = realloc(numConsts, sizeof(double) *  maxNumConsts);
		if(tmp != NULL) {
			numConsts = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	numConsts[totalNumConsts] = n;
	
	return totalNumConsts++;

}

/* Returns the position of a constant string in the constant strings array,
   if it doesnt exist it is inserted */
unsigned int consts_newstring(char *s) {

	int i = 0;
	
	for(i = 0; i < totalStringConsts; i++) {
		if(strcmp(s, stringConsts[i]) == 0) return i;
	}
	
	if(totalStringConsts == maxStringConsts) {
		maxStringConsts = maxStringConsts * 2;
		char **tmp = realloc(stringConsts, sizeof(char*) *  maxStringConsts);
		if(tmp != NULL) {
			stringConsts = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	stringConsts[totalStringConsts] = strdup(s);
	
	return totalStringConsts++;

}

/* Returns the position of a user function in the user functions array,
   if it doesnt exist it is inserted */
unsigned int userfuncs_newfunc(SymbolTableEntry *entry) {
	
	int i = 0;

	for(i = 0; i < totalUserFuncs; i++) {
		if(userFuncs[i].address == entry->address) return i;
	}

	if(totalUserFuncs == maxNumConsts) {
		maxUserFuncs = maxUserFuncs * 2;
		UserFunc *tmp = realloc(userFuncs, sizeof(UserFunc) *  maxUserFuncs);
		if(tmp != NULL) {
			userFuncs = tmp;	
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}
	}
	UserFunc f;
	f.address = entry->address;
	f.localSize = entry->totallocals;
	f.id = strdup(entry->name);
	userFuncs[totalUserFuncs] = f;
	
	return totalUserFuncs++;

}

/* Returns the position of a library function in the library functions array,
   if it doesnt exist it is inserted */
unsigned int libfuncs_newused(char *s) {

	int i = 0;
	
	for(i = 0; i <  totalNamedLibfuncs; i++) {
		if(strcmp(s, namedLibfuncs[i]) == 0) return i;
	}
	
	namedLibfuncs[totalNamedLibfuncs] = strdup(s);
	
	return  totalNamedLibfuncs++;

}

/* Prints a virtual machine argument */
void print_vmarg(FILE *file, VMarg arg) {
		
	if(arg.type != omit_a) {
		if(arg.type == retval_a) fprintf(file, "%d   ", arg.type);
		else fprintf(file, "%d %d   ", arg.type, arg.val);
	}
	
	return;

}

/* Prints a virtual machine argument in binary form */
void print_binary_vmarg(FILE *bfile, VMarg arg) {

	fwrite(&arg.type, sizeof(VMargType), 1, bfile);
	fwrite(&arg.val, sizeof(unsigned int), 1, bfile);
	
	return;

}

/* Prints the instructions */
void print_instructions(const char *path) {

	int i = 0;
	
	if(error_flag) return;

	FILE *file = fopen(path, "w");
	if(file == NULL) {
		fprintf(stderr, "Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < currInstr; i++) {
		// print (#:)(1 space)(x)(3 spaces)
		fprintf(file, "%d: %s   ", i, vmopcode_to_string(instructions[i].opcode));
		print_vmarg(file, instructions[i].arg1);
		print_vmarg(file, instructions[i].arg2);
		print_vmarg(file, instructions[i].result);
		fprintf(file, "\n");
	}

	fclose(file);

	return;
	
}

/* Prints the binary file */
void print_binary_file(const char *tpath, const char *bpath) {

	int i = 0;
	long int magic_number = MAGIC_NUMBER;
	size_t string_length = 0;
	
	// SIMPLE FILE (fprintf)
	FILE *tfile = fopen(tpath, "w");
	if(tfile == NULL) {
		fprintf(stderr, "Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	// BINARY FILE (fwrite)
	FILE *bfile = fopen(bpath, "wb");
	if(bfile == NULL) {
		fprintf(stderr, "Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fprintf(tfile, "%ld\n", magic_number);
	fwrite(&magic_number, sizeof(long int), 1, bfile);

	fprintf(tfile, "%d\n", totalNumConsts);
	fwrite(&totalNumConsts, sizeof(unsigned int), 1, bfile);
	for(i = 0; i < totalNumConsts; i++) {
		fprintf(tfile, "%f\n", numConsts[i]);
		fwrite(&numConsts[i], sizeof(double), 1, bfile);
	}
	
	fprintf(tfile, "%d\n", totalStringConsts);
	fwrite(&totalStringConsts, sizeof(unsigned int), 1, bfile);
	for(i = 0; i < totalStringConsts; i++) {
		string_length = strlen(stringConsts[i]);
		fprintf(tfile, "%zu %s\n", string_length, stringConsts[i]);
		fwrite(&string_length, sizeof(size_t), 1, bfile);
		fwrite(stringConsts[i], sizeof(char), string_length, bfile);
	}

	fprintf(tfile, "%d\n", totalUserFuncs);
	fwrite(&totalUserFuncs, sizeof(unsigned int), 1, bfile);
	for(i = 0; i < totalUserFuncs; i++) {
		string_length = strlen(userFuncs[i].id);
		fprintf(tfile, "%d %d %zu %s\n", userFuncs[i].address, userFuncs[i].localSize, string_length, userFuncs[i].id);
		fwrite(&userFuncs[i].address, sizeof(unsigned int), 1, bfile);
		fwrite(&userFuncs[i].localSize, sizeof(unsigned int), 1, bfile);
		fwrite(&string_length, sizeof(size_t), 1, bfile);
		fwrite(userFuncs[i].id, sizeof(char), string_length, bfile);
	}

	fprintf(tfile, "%d\n", totalNamedLibfuncs);
	fwrite(&totalNamedLibfuncs, sizeof(unsigned int), 1, bfile);
	for(i = 0; i < totalNamedLibfuncs; i++) {
		string_length = strlen(namedLibfuncs[i]);
		fprintf(tfile, "%zu %s\n", string_length, namedLibfuncs[i]);
		fwrite(&string_length, sizeof(size_t), 1, bfile);
		fwrite(namedLibfuncs[i], sizeof(char), string_length, bfile);
	}
	
	fprintf(tfile, "%d\n", currInstr);
	fwrite(&currInstr, sizeof(unsigned int), 1, bfile);
	for(i = 0; i < currInstr; i++) {
		fprintf(tfile, "%d   ", instructions[i].opcode);
		fwrite(&instructions[i].opcode, sizeof(VirtualMachineOpCode), 1, bfile);
		print_vmarg(tfile, instructions[i].arg1);
		print_binary_vmarg(bfile, instructions[i].arg1);
		print_vmarg(tfile, instructions[i].arg2);
		print_binary_vmarg(bfile, instructions[i].arg2);
		print_vmarg(tfile, instructions[i].result);
		print_binary_vmarg(bfile, instructions[i].result);
		fprintf(tfile, "%d", instructions[i].srcLine);
		fwrite(&instructions[i].srcLine, sizeof(unsigned int), 1, bfile);
		fprintf(tfile, "\n");
	}

	fclose(tfile);
	fclose(bfile);

	return;

}