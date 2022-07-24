%{

	#include "symtable.h"
	#define yylex alpha_yylex
	#define PTEST(x) fprintf(stderr, "PARSER(%d)\n", x);
	
	extern void yyerror(char *providedMessage);
	extern int alpha_yylex();
	extern void alpha_yylex_test();
	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
	
	//TODO LIST
	/*
	
	*NT: NEEDS TEST | V: VERIFIED*
	
	SAME SCOPE IN DIFFERENT BLOCKS -> DONE(NT)
	
	NOT SURE IF ACTIONS ARE NEEDED IN MEMBER OR METHODCALL -> DONE(V)
	
	ADD (STUPID) LIBFUNC CHECK IN FORMAL ARGUMENTS BEACAUSE PDF SAYS SO -> DONE(NT)
	
	CHECK THE MIGTHY VARIABLE X(front3-final slide) -> DONE(NT)
	
	CHECK THE lvalue->id thing(front3-final slide) -> DONE(NT!!! - local y++)
	
	SCOPE_SENTINEL CHECK IF THE FIRST IS INACTIVE -> DONE(NT)
	
	FUNCTION ARGUMENTS -> DONE(NT)
	
	CHECK GETFUNCNAME FUNCTION(UNNAMED FUNCTIONS) -> DONE(NT)
	
	CHECK FUNCTION ARGUMENTS IF FUNCTION IS WRONG -> DONE(V)
	
	BLOCK INSIDE FUNCTION -> DONE(NT)
	
	*/
	
%}

%start program

%union {
	char	*sval;
	int		ival;
	float	fval;
	SymbolTableEntry *eval;
}

%token	<sval>	ID STRING_LITERAL;
%token	<ival>	INTEGER;
%token	<fval>	REAL;
%token	<ival>	IF ELSE WHILE FOR FUNCTION RETURN BREAK 
%token	<ival>	CONTINUE AND NOT OR LOCAL IS_TRUE IS_FALSE NIL
%token	<ival>	ASSIGN PLUS MINUS STAR SLASH MOD EQUAL UNEQUAL PLUS_PLUS 
%token	<ival>	MINUS_MINUS GREATER LESSER GREATER_OR_EQUAL LESSER_OR_EQUAL
%token	<ival>	BLOCK_START BLOCK_END BRACKET_OPEN BRACKET_CLOSE PARENTHESES_OPEN PARENTHESES_CLOSE
%token	<ival>	SEMICOLON COMMA COLON SCOPE DOT DOT_DOT

%type <eval> lvalue

%right ASSIGN
%left OR
%left AND 
%nonassoc EQUAL UNEQUAL
%nonassoc GREATER GREATER_OR_EQUAL LESSER LESSER_OR_EQUAL 
%left PLUS MINUS
%left STAR SLASH MOD
%right NOT PLUS_PLUS MINUS_MINUS UNARY_MINUS /* MINUS expr -> %prec UNARY_MINUS */
%left DOT DOT_DOT
%left BRACKET_OPEN BRACKET_CLOSE
%left PARENTHESES_OPEN PARENTHESES_CLOSE
%right THEN ELSE /* THEN and ELSE have same precedence and right associativity */


%%


program : stmts { printf("line:%d  program: stmts\n",yylineno); }
		;
		
stmts	: stmts stmt  { printf("line:%d  stmts stmt\n",yylineno); }
		| /* empty */ { printf("line:%d  empty\n",yylineno); }
		;
		
stmt	: expr SEMICOLON	 { printf("line:%d  expr;\n",yylineno); }
		| ifstmt			 { printf("line:%d  ifstmt\n",yylineno); }
		| whilestmt          { printf("line:%d  whilestmt\n",yylineno); }
		| forstmt			 { printf("line:%d  forstmt\n",yylineno); }
		| returnstmt		 { printf("line:%d  returnstmt\n",yylineno); }
		| BREAK SEMICOLON	 { printf("line:%d  break;\n",yylineno); }
		| CONTINUE SEMICOLON { printf("line:%d  continue;\n",yylineno); }
		| block				 { printf("line:%d  block\n",yylineno); }
		| funcdef			 { printf("line:%d  funcdef\n",yylineno); }
		| SEMICOLON          { printf("line:%d  ;\n",yylineno); }
		;
		
expr	: assignexpr				 { printf("line:%d  assignexpr\n",yylineno); }
		| expr PLUS expr 			 { printf("line:%d  expr + expr\n",yylineno); }
		| expr MINUS expr			 { printf("line:%d  expr - expr\n",yylineno); }
		| expr STAR expr			 { printf("line:%d  expr * expr\n",yylineno); }
		| expr SLASH expr			 { printf("line:%d  expr / expr\n",yylineno); }
		| expr MOD expr				 { printf("line:%d  expr %% expr\n",yylineno); }
		| expr GREATER expr			 { printf("line:%d  expr > expr\n",yylineno); }
		| expr GREATER_OR_EQUAL expr { printf("line:%d  expr >= expr\n",yylineno); }
		| expr LESSER expr			 { printf("line:%d  expr < expr\n",yylineno); }
		| expr LESSER_OR_EQUAL expr	 { printf("line:%d  expr <= expr\n",yylineno); }
		| expr EQUAL expr			 { printf("line:%d  expr = expr\n",yylineno); }
		| expr UNEQUAL expr			 { printf("line:%d  expr != expr\n",yylineno); }
		| expr AND expr				 { printf("line:%d  expr && expr\n",yylineno); }
		| expr OR expr				 { printf("line:%d  expr || expr\n",yylineno); }
		| term						 { printf("line:%d  term\n",yylineno); }
		;
		
term	: PARENTHESES_OPEN expr PARENTHESES_CLOSE { printf("line:%d  (expr)\n",yylineno); }
		| MINUS expr %prec UNARY_MINUS			  { printf("line:%d  -expr\n",yylineno); }
		| NOT expr								  { printf("line:%d  not expr\n",yylineno); }
		| PLUS_PLUS lvalue {
		
			if($2) {
				if($2->type == USERFUNC || $2->type == LIBFUNC) {
					yyerror("error: functions cannot be used as lvalue");
				}
			}
			
			printf("line:%d  ++lvalue\n",yylineno);
			
		  }
		| lvalue PLUS_PLUS {
		
			if($1) {
				if($1->type == USERFUNC || $1->type == LIBFUNC) {
					yyerror("error: functions cannot be used as lvalue");
				}
			}
			
			printf("line:%d  lvalue++\n",yylineno);
			 
		  }
		| MINUS_MINUS lvalue {
		
			if($2) {
				if($2->type == USERFUNC || $2->type == LIBFUNC) {
					yyerror("error: functions cannot be used as lvalue");
				}
			}
			
			printf("line:%d  --lvalue\n",yylineno);
			
		  }
		| lvalue MINUS_MINUS {
		
			if($1) {
				if($1->type == USERFUNC || $1->type == LIBFUNC) {
					yyerror("error: functions cannot be used as lvalue");
				}
			}
			
			printf("line:%d  lvalue--\n",yylineno);
			 
		  }
		| primary { printf("line:%d  primary\n",yylineno); }
		;
		
assignexpr	: lvalue ASSIGN expr {

				if($1) {
					if($1->type == USERFUNC || $1->type == LIBFUNC) {
						yyerror("error: functions cannot be used as lvalue");
					}	
				}

				printf("line:%d  lvalue = expr\n",yylineno); 
				
			  }
			;
			
primary	: lvalue									 { printf("line:%d  lvalue\n",yylineno); }
		| call										 { printf("line:%d  call\n",yylineno); }
		| objectdef									 { printf("line:%d  objectdef\n",yylineno); }		
		| PARENTHESES_OPEN funcdef PARENTHESES_CLOSE { printf("line:%d  (funcdef)\n",yylineno); }
		| const										 { printf("line:%d  const\n",yylineno); }
		;
			
lvalue	: ID {

			/* lookup, starting from the currently active scope, ending at the global scope */
			SymbolTableEntry *entry = lookup(yytext);
			if(entry) {
				if(!isAccessible(entry)) yyerror("error: symbol is not accessible");
				$$ = entry;
			}else {
				if(active_scope == 0) insert(yytext, active_scope, yylineno, GLOBALVAR, NULL, -1);
				else insert(yytext, active_scope, yylineno, VARVAR, NULL, -1);
				$$ = NULL;
			}
			printf("***********SOS*****\n%s\n", yytext);
			printf("%s\n", $1);
			
			printf("line:%d  id\n",yylineno);
			
		  }	
		| LOCAL ID {
			
			/* lookup on the currently active scope */
			SymbolTableEntry *entry = lookup_on_scope(yytext, active_scope);
			if(active_scope != 0 && isLibFunc(yytext)) {
				yyerror("error: library functions cannot be shadowed");
				$$ = lookup(yytext);
			}else if(entry) {
				$$ = entry;
			}else {
				if(active_scope == 0) insert(yytext, active_scope, yylineno, GLOBALVAR, NULL, -1);
				else insert(yytext, active_scope, yylineno, LOCALVAR, NULL, -1);
				$$ = NULL;
			}
			
			printf("line:%d  local id\n",yylineno);
			 
		  }     
		| SCOPE ID {
			
			/* lookup on the global scope */
			SymbolTableEntry *entry = lookup_on_scope(yytext, 0);
			if(entry) {
				$$ = entry;
			}else {
				yyerror("error: symbol not found");
				$$ = NULL;
			}
			
			printf("line:%d  ::id\n",yylineno);
			 
		  }
		| member { printf("line:%d  member\n",yylineno); }	
		;
			
member	: lvalue DOT ID							 { printf("line:%d  lvalue.id\n",yylineno); }	
		| lvalue BRACKET_OPEN expr BRACKET_CLOSE { printf("line:%d  lvalue[expr]\n",yylineno); }
		| call DOT ID							 { printf("line:%d  call.id\n",yylineno); }
		| call BRACKET_OPEN expr BRACKET_CLOSE	 { printf("line:%d  call[expr]\n",yylineno); }
		;
			
call	: call PARENTHESES_OPEN elist PARENTHESES_CLOSE										  { printf("line:%d  call(elist)\n",yylineno); }
		| lvalue callsuffix																	  { printf("line:%d  lvalue callsuffix\n",yylineno); }
		| PARENTHESES_OPEN funcdef PARENTHESES_CLOSE PARENTHESES_OPEN elist PARENTHESES_CLOSE { printf("line:%d  (funcdef)(elist)\n",yylineno); }
		;
		
callsuffix	: normcall   { printf("line:%d  normcall\n",yylineno); }
			| methodcall { printf("line:%d  methodcall\n",yylineno); }
			;
			
normcall	: PARENTHESES_OPEN elist PARENTHESES_CLOSE { printf("line:%d  (elist)\n",yylineno); }
			;
			
methodcall	: DOT_DOT ID PARENTHESES_OPEN elist PARENTHESES_CLOSE { printf("line:%d  ..id(elist)\n",yylineno); }
			;
			
elist	: elist_plus  { printf("line:%d  elist_plus\n",yylineno); }
		| /* empty */ { printf("line:%d  empty\n",yylineno); }
		;
			
elist_plus	: expr  				{ printf("line:%d  expr\n",yylineno); }
			| elist_plus COMMA expr { printf("line:%d  elist_plus,expr\n",yylineno); }
			;
		
objectdef	: BRACKET_OPEN elist BRACKET_CLOSE   { printf("line:%d  [elist]\n",yylineno); }
			| BRACKET_OPEN indexed BRACKET_CLOSE { printf("line:%d  [indexed]\n",yylineno); }
			;
			
indexed	: indexedelem				{ printf("line:%d  indexedelem\n",yylineno); }
		| indexed COMMA indexedelem { printf("line:%d  indexed,indexedelem\n",yylineno); }
		;
		
indexedelem	: BLOCK_START expr COLON expr BLOCK_END { printf("line:%d  {expr:expr}\n",yylineno); }
			;
			
block	: BLOCK_START {
 
		  	if(!funcflag && !whileflag && !forflag) {
		  		if(++active_scope > scope_depth) scope_depth++;
		  	}else{
		  		funcflag = 0;
		  		whileflag =0;
		  		forflag = 0;
		  	}
		  	
		  }
		  stmts 
		  BLOCK_END {
		  
		  	hide(active_scope--);
		  	printf("line:%d  {stmts}\n",yylineno);
		  	
		  }
		;
		
funcdef	: FUNCTION ID {

			/* lookup on the currently active scope */
			SymbolTableEntry *entry = lookup_on_scope(yytext, active_scope);
			if(isLibFunc(yytext)) {
				yyerror("error: library functions cannot be shadowed");
			}else if(entry) {
				yyerror("error: symbol already defined");
			}else{
				func_entry = insert(yytext, active_scope, yylineno, USERFUNC, NULL, -1);	
			}
			
		  }
		  PARENTHESES_OPEN {
		  
		  	funcflag = 1;
			if(++active_scope > scope_depth) scope_depth++;
			
		  } 
		  idlist {
		  
		  	if(func_entry) {
		  		func_entry->argc = funcargc;
				func_entry->args = funcargs;
			  	reset_funcargs();
			}
		  	
		  } 
		  PARENTHESES_CLOSE block { printf("line:%d  function id (idlist) block\n",yylineno); }
		| FUNCTION {
		
			/* no lookup needed */
			func_entry = insert(get_funcname(), active_scope, yylineno, USERFUNC, NULL, -1);
			
		  }
		  PARENTHESES_OPEN {
		  
			funcflag = 1;
			if(++active_scope > scope_depth) scope_depth++;
			
		  }
		  idlist {
		  
	  		func_entry->argc = funcargc;
			func_entry->args = funcargs;
		  	reset_funcargs();
		  
		  } 
		  PARENTHESES_CLOSE block { printf("line:%d  function (idlist) block\n",yylineno); }
		;
		
const	: INTEGER        {printf("line:%d  integer\n",yylineno);}
		| REAL			 {printf("line:%d  real\n",yylineno);}	
		| STRING_LITERAL {printf("line:%d  string\n",yylineno);}
		| NIL			 {printf("line:%d  nil\n",yylineno);}
		| IS_TRUE        {printf("line:%d  true\n",yylineno);}
		| IS_FALSE   	 {printf("line:%d  false\n",yylineno);}
		;
		
idlist	: idlist_plus {printf("line:%d  idlist_plus\n",yylineno);}
		| /* empty */ {printf("line:%d  empty\n",yylineno);}
		;
		
idlist_plus	: ID {				
				
				/* lookup on the currently active scope */
				if(isLibFunc(yytext)) {
					yyerror("error: library functions cannot be shadowed");
				}else {
					insert(yytext, active_scope, yylineno, FORMALVAR, NULL, -1);
					if(func_entry) {
						if(funcargc == max_funcargc) grow_funcargs();
						funcargs[funcargc++] = strdup(yytext);
					}
				}
				
				printf("line:%d  id\n",yylineno);
				
			  }
			| idlist_plus COMMA ID {
				
				/* lookup on the currently active scope */
				SymbolTableEntry *entry = lookup_on_scope(yytext, active_scope);
				if(isLibFunc(yytext)) {
					yyerror("error: library functions cannot be shadowed");
				}else if(entry) {
					yyerror("error: symbol already defined");
				}else {
					insert(yytext, active_scope, yylineno, FORMALVAR, NULL, -1);
					
					if(func_entry) {
						if(funcargc == max_funcargc) grow_funcargs();
						funcargs[funcargc++] = strdup(yytext);
					}
				}
				
				printf("line:%d  idlist_plus,id\n",yylineno);
				
			  }
			;
		
ifstmt	: IF PARENTHESES_OPEN expr PARENTHESES_CLOSE stmt ELSE stmt  {printf("line:%d  if(expr)stmt else stmt\n",yylineno);}
		| IF PARENTHESES_OPEN expr PARENTHESES_CLOSE stmt %prec THEN {printf("line:%d  if(expr)stmt\n",yylineno);}
		;
		
whilestmt	: WHILE PARENTHESES_OPEN {
				whileflag = 1;
				if(++active_scope > scope_depth) scope_depth++;
			  } 
			  expr PARENTHESES_CLOSE stmt {printf("line:%d  while(expr)stmt\n",yylineno);}
			;
			
forstmt	: FOR PARENTHESES_OPEN {
			forflag = 1;
			if(++active_scope > scope_depth) scope_depth++;
		  } 
		  elist SEMICOLON expr SEMICOLON elist PARENTHESES_CLOSE stmt {printf("line:%d  for(elist;expr;elist)stmt\n",yylineno);}
		;
		
returnstmt	: RETURN expr SEMICOLON {printf("line:%d  return expr;\n",yylineno);}
			| RETURN SEMICOLON		{printf("line:%d  return;\n",yylineno);}
			;
			

%%

int main(int argc,char **argv) {

	int flag = 0;
	
   	++argv, --argc; /* skipping over program name */
    switch(argc) {
        case 0:
            yyin = stdin;
            break;
        case 2:
        	if(strcmp(argv[1], "-test") == 0) {
        		flag = 1;
        	}else {
        		fprintf(stderr, "Unknown option\n");
        		exit(EXIT_FAILURE);
        	}
        case 1:
        	if(!(yyin = fopen(argv[0], "r"))) {
				fprintf(stderr, "Cannot read file: %s\n", argv[0]);
				return 1;
			}
			break;
        default:
            assert(0);
    }

	if(flag) { 
		/* RUN TESTS */
		alpha_yylex_test();
	}else { 
		/* RUN PARSER */
		symbolTableInit();
		yyparse();
		free_ins_vars();
		print_symbol_table();
		print_scope_lists();
	}

    return 0;
    
}

