#ifndef TARGET_H_
#define TARGET_H_

#include "intermediate.h"

#define MAGIC_NUMBER 5402982071
#define MAX_NUMCONSTS 30
#define MAX_STRINGCONSTS 20
#define MAX_NAMEDLIBFUNCS 12
#define MAX_USERFUNCS 10
#define TOP_NUM 24
#define EXPAND_INSTR_SIZE 1024
#define CURR_INSTR_SIZE (totalInstr * sizeof(Instruction))
#define NEW_INSTR_SIZE (EXPAND_INSTR_SIZE * sizeof(Instruction) + CURR_INSTR_SIZE)

typedef void (*generator_func_t)(Quad*); 

typedef enum VMOpCode {
	assign_v, add_v, sub_v,
	mul_v, div_v, mod_v,
	jeq_v, jne_v, jle_v, jge_v, 
	jlt_v, jgt_v, call_v, pusharg_v, 
	funcenter_v, funcexit_v, 
	newtable_v, tablegetelem_v, 
	tablesetelem_v, jump_v, nop_v
} VirtualMachineOpCode;

typedef enum VMargType {
	label_a = 0,
	global_a = 1,
	formal_a = 2,
	local_a = 3,
	number_a = 4,
	string_a = 5,
	bool_a = 6,
	nil_a = 7,
	userfunc_a = 8, 
	libfunc_a = 9,
	retval_a = 10,
	omit_a = 11
} VMargType;

typedef struct UserFunction {
	unsigned int address;
	unsigned int localSize;
	char *id;
} UserFunc;

typedef struct VirtualMachineMarg {
	VMargType type;
	unsigned int val;
} VMarg;

typedef struct InstructionInfo {
	VirtualMachineOpCode 		opcode;
	VMarg 						arg1;
	VMarg 						arg2;
	VMarg 						result;
	unsigned int				srcLine;
} Instruction;

typedef struct IncompleteJump {
	unsigned int	instrNo;
	unsigned int 	iaddress;
	struct IncompleteJump *next;
} IncompleteJump;

extern Quad *quads;
extern unsigned int currQuad;

Instruction *instructions;
unsigned int currInstr;
unsigned int totalInstr;
unsigned int currprocessedquad;

IncompleteJump *ij_head; 
unsigned ij_total;

double *numConsts;
unsigned int totalNumConsts;
unsigned int maxNumConsts;
char **stringConsts;
unsigned int totalStringConsts;
unsigned int maxStringConsts;
UserFunc *userFuncs;
unsigned int totalUserFuncs;
unsigned int maxUserFuncs;
char **namedLibfuncs;
unsigned int totalNamedLibfuncs;


/* Returns the string represantation of the given opcode */
char* vmopcode_to_string(IntermediateOpCode op);

/* Returns a new empty instruction */
Instruction new_instr();

/* Initializes the target code generation variables */
void target_init();

/* Initializes the incomplete jump variables variables */
void ijump_init();

/* Initializes the variables needed to store
   n : constant numbers
   s : constant numbers
   u : user functions
   l : library functions */
void nsul_init();

/* Inserts a jump in the incomplete jump list */
void add_incomplete_jump(unsigned instrNo, unsigned iaddress);

/* Patches incomplete jumps */
void patch_incomplete_jump();

/* Grows the instruction array */
void expand_instr();

/* Stores an isntruction in the instruction array */
void emit_instr(Instruction t);

/* Produces an operand */
void make_operand(Expr *e, VMarg *arg);

/* Produces numbers for generated instructions */
void make_numberoperand(VMarg *arg, double val);

/* Produces booleans for generated instructions */
void make_booloperand(VMarg *arg, unsigned char val);

/* Produces return values for generated instructions */
void make_retvaloperand(VMarg *arg);

/* Produces omit values for generated instructions */
void reset_operand(VMarg *arg);

/* Generates an instruction */
void generate(VirtualMachineOpCode op, Quad *quad);

/* Generates a relational instruction */
void generate_relational(VirtualMachineOpCode op, Quad *quad);

/* Generates an assign instruction */
void generate_ASSIGN(Quad *quad);

/* Generates an add instruction */
void generate_ADD(Quad *quad);

/* Generates a sub instruction */
void generate_SUB(Quad *quad);
 
 /* Generates a mul instruction */
void generate_MUL(Quad *quad);

/* Generates a div instruction */
void generate_DIV(Quad *quad);

/* Generates a mod instruction */
void generate_MOD(Quad *quad);

/* Generates a newtable instruction */
void generate_NEWTABLE(Quad *quad);

/* Generates a tablegetelem instruction */
void generate_TABLEGETELM(Quad *quad);

/* Generates a tablesetelem instruction */
void generate_TABLESETELEM(Quad *quad);

/* Generates a nop instruction */
void generate_NOP();

/* Generates a jump instruction */
void generate_JUMP(Quad *quad);

/* Generates an if_eq instruction */
void generate_IF_EQ(Quad *quad);

/* Generates an if_noteq instruction */
void generate_IF_NOTEQ(Quad *quad);

/* Generates an if_lesseq instruction */
void generate_IF_LESSEQ(Quad *quad);

/* Generates an if_greatereq instruction */
void generate_IF_GREATEREQ(Quad *quad);

/* Generates an if_less instruction */
void generate_IF_LESS(Quad *quad);

/* Generates an if_greater instruction */
void generate_IF_GREATER(Quad *quad);

/* Generates a uminus instruction */
void generate_UMINUS(Quad *quad);

/* Generates a not instruction */
void generate_NOT(Quad *quad);

/* Generates an and instruction */
void generate_AND(Quad *quad); 

/* Generates an or instruction */
void generate_OR(Quad *quad);

/* Generates a param istruction */
void generate_PARAM(Quad *quad);

/* Generates a call instruction */
void generate_CALL(Quad *quad);

/* Generates a call instruction */
void generate_GETRETVAL(Quad *quad);

/* Generates a funcstart instruction */
void generate_FUNCSTART(Quad *quad);

/* Generates a funcend instruction */
void generate_FUNCEND(Quad *quad);

/* Generates a return instruction */
void generate_RETURN(Quad *quad);

/* Calls a generator for each quad */
void generate_instructions();

/* Returns the position of a constant number in the constant numbers array,
   if it doesnt exist it is inserted */
unsigned int consts_newnumber(double n);

/* Returns the position of a constant string in the constant strings array,
   if it doesnt exist it is inserted */
unsigned int consts_newstring(char *s);

/* Returns the position of a user function in the user functions array,
   if it doesnt exist it is inserted */
unsigned int userfuncs_newfunc(SymbolTableEntry *entry);

/* Returns the position of a library function in the library functions array,
   if it doesnt exist it is inserted */
unsigned int libfuncs_newused(char *s);

/* Prints a virtual machine argument */
void print_vmarg(FILE *file, VMarg arg);

/* Prints a virtual machine argument in binary form */
void print_binary_vmarg(FILE *bfile, VMarg arg);

/* Prints the instructions */
void print_instructions(const char *path);

/* Prints the binary file */
void print_binary_file(const char *tpath, const char *bpath);

#endif