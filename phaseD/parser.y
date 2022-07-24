%{

    #ifdef SKERDI_NEEDS_THIS_STUPID_DEFINE_
    #define SKERDI_NEEDS_THIS_STUPID_DEFINE_
    #endif
	
	#include "target.h"
	#include <sys/stat.h>
	
    #define yylex alpha_yylex
    #define PTEST(x) fprintf(stderr, "PARSER(%d)\n", x);
    
    extern void yyerror(char *providedMessage);
    extern int alpha_yylex();
    extern void alpha_yylex_test();
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    
	/* Rest in peace TODO list */
    
%}

%start program

%union {
    char				*sval;
    int					ival;
    double				rval;
    SymbolTableEntry	*eval;
    Expr 				*xval;
    CallsuffixObj 		*cval;
	ForprefixObj 		*fval;
}

%token	<sval>	ID STRING_LITERAL
%token	<ival>	INTEGER
%token	<rval>	REAL
%token	<ival>	IF ELSE WHILE FOR FUNCTION RETURN BREAK 
%token	<ival>	CONTINUE AND NOT OR LOCAL IS_TRUE IS_FALSE NIL
%token	<ival>	ASSIGN PLUS MINUS STAR SLASH MOD EQUAL UNEQUAL PLUS_PLUS 
%token	<ival>	MINUS_MINUS GREATER LESSER GREATER_OR_EQUAL LESSER_OR_EQUAL
%token	<ival>	BLOCK_START BLOCK_END BRACKET_OPEN BRACKET_CLOSE PARENTHESES_OPEN PARENTHESES_CLOSE
%token	<ival>	SEMICOLON COMMA COLON SCOPE DOT DOT_DOT

%type <xval> lvalue member primary assignexpr
%type <xval> call term objectdef const
%type <xval> expr elist elist_plus tableitem
%type <xval> tablemake indexed indexedelem
%type <cval> callsuffix normcall methodcall
%type <sval> funcname
%type <ival> funcbody
%type <eval> funcprefix funcdef
%type <fval> forprefix
%type <xval> forstmt
%type <ival> whilestart whilecond ifprefix elseprefix
%type <ival> N
%type <ival> M

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


program : stmts
        ;
        
stmts	: stmts stmt  {
			tmpnum = 0;
		  }
        | /* empty */
        ;
        
stmt	: expr SEMICOLON
        | ifstmt
        | whilestmt
        | forstmt
        | returnstmt {
			add_stop(&return_list);
			emit(jump, NULL, NULL, NULL, 0);
		  }
        | BREAK SEMICOLON {
			if(loopcounter > 0){
				add_stop(&break_list);
				emit(jump, NULL, NULL, NULL, 0);
			}else {
				yyerror("error: break out of loop block");
			}
          }
        | CONTINUE SEMICOLON {
			if(loopcounter > 0){
				add_stop(&continue_list);
				emit(jump, NULL, NULL, NULL, 0);
			}else {
				yyerror("error: continue out of loop block");
			}
          }
        | block
        | funcdef
        | SEMICOLON
        ;
        
expr	: assignexpr
        | expr PLUS expr {
			$$ = make_arithop(add, $1, $3);
          }                        
        | expr MINUS expr {  
            $$ = make_arithop(sub, $1, $3);		
          }                              
        | expr STAR expr {
            $$ = make_arithop(mul, $1, $3); 
          }                             
        | expr SLASH expr {
            $$ = make_arithop(divide, $1, $3);
          }                             
        | expr MOD expr	{
            $$ = make_arithop(mod, $1, $3);
          }                               
        | expr GREATER expr	{
            $$ = make_relop(if_greater, $1, $3);
          }                             
        | expr GREATER_OR_EQUAL expr {
            $$ = make_relop(if_greatereq, $1, $3);
          }                             
        | expr LESSER expr {
            $$ = make_relop(if_less, $1, $3); 
          }                             
        | expr LESSER_OR_EQUAL expr	{
            $$ = make_relop(if_lesseq, $1, $3); 
          }                            
        | expr EQUAL expr {
            $$ = make_relop(if_eq, $1, $3); 
          }                           
        | expr UNEQUAL expr {
            $$ = make_relop(if_noteq, $1, $3); 
          }                         
        | expr AND expr	{
            $$ = make_boolop(and, $1, $3);
          }                           
        | expr OR expr { 
            $$ = make_boolop(or, $1, $3);                           
          }
        | term {
            $$ = $1;
          }
        ;
        
term	: PARENTHESES_OPEN expr PARENTHESES_CLOSE {
            $$ = $2;
          }
        | MINUS expr %prec UNARY_MINUS {
			$$ = make_arithop(mul, newexpr_constnum(-1), $2);
          }
        | NOT expr {
            $$ = newexpr(boolexpr_e);
            $$->sym = newtmp();
            emit(not, $2, NULL, $$, 0);
          }
        | PLUS_PLUS lvalue {
			if(get_primitive_type($2->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            $$ = make_opterm(add, $2); 
          }
        | lvalue PLUS_PLUS {
			if(get_primitive_type($1->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            $$ = make_termop(add, $1);
          }
        | MINUS_MINUS lvalue {
			if(get_primitive_type($2->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            $$ = make_opterm(sub, $2);
          }
        | lvalue MINUS_MINUS {
			if(get_primitive_type($1->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            $$ = make_termop(sub, $1);
          }
        | primary {
            $$ = $1;
          }
        ;
        
assignexpr  : lvalue ASSIGN expr {
				if(get_primitive_type($1->sym->type) != VAR_S) {
					yyerror("error: functions cannot be used as lvalue");
				}
                $$ = make_assign($1, $3);        
              }
            ;
            
primary : lvalue {
			$$ = make_iftableitem($1);
		  }
		| call
		| objectdef
		| PARENTHESES_OPEN funcdef PARENTHESES_CLOSE {
			$$ = newexpr(programfunc_e);
			$$->sym = $2;
		  }
		| const	{
            $$ = $1; 
          }
		;
            
lvalue	: ID {
            /* lookup, starting from the currently active scope, ending at the global scope */
            SymbolTableEntry *entry = lookup($1);               
            if(entry) {
                if(!is_accessible(entry)) yyerror("error: symbol is not accessible");
            }else {
                if(active_scope == 0) entry = insert($1, active_scope, yylineno, GLOBALVAR, NULL, -1);
                else entry = insert($1, active_scope, yylineno, VARVAR, NULL, -1);
            }
            $$ = make_lvalue_expr(entry);
          }	
        | LOCAL ID {
            /* lookup on the currently active scope */
            SymbolTableEntry *entry = lookup_on_scope($2, active_scope);
            if(active_scope != 0 && is_lib_func($2)) {
                yyerror("error: library functions cannot be shadowed");
                entry = lookup_on_scope($2, 0);
            }else if(!entry) {
                if(active_scope == 0) entry = insert($2, active_scope, yylineno, GLOBALVAR, NULL, -1);
                else entry = insert($2, active_scope, yylineno, LOCALVAR, NULL, -1);
            }
            $$ = make_lvalue_expr(entry);  
          }     
        | SCOPE ID {
            /* lookup on the global scope */
            SymbolTableEntry *entry = lookup_on_scope($2, 0);
            if(!entry) {
                yyerror("error: symbol not found");
				entry = new_empty_entry();
				entry->name = "_missingno";
            }
            $$ = make_lvalue_expr(entry);
          }
        | member
        ;

tableitem	: lvalue DOT ID { 
                $$ = make_member_item($1, $3); 
              }
            | lvalue BRACKET_OPEN expr BRACKET_CLOSE {
                $1 = make_iftableitem($1);
                $$ = newexpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;
              }  
            ;
            
member	: tableitem
        | call DOT ID
        | call BRACKET_OPEN expr BRACKET_CLOSE
        ;
            
call	: call PARENTHESES_OPEN elist PARENTHESES_CLOSE {
		    $$ = make_call($1, $3);
		  }
		| lvalue callsuffix	{
			if($2->method) {
				Expr *self = $1;
				$1 = make_iftableitem(make_member_item(self, $2->name));
				Expr *tmp = $2->elist;
				if(tmp != NULL) {
					while(tmp->next != NULL) tmp = tmp->next;
				}
				tmp->next = self;
		  	}
			$$ = make_call($1, $2->elist);
		  }
		| PARENTHESES_OPEN funcdef PARENTHESES_CLOSE PARENTHESES_OPEN elist PARENTHESES_CLOSE { 
			Expr *func = newexpr(programfunc_e);
			func->sym = $2;
			$$ = make_call(func, $5);
		  }
		;
        
callsuffix	: normcall {
                $$ = $1;
              }
            | methodcall {
                $$ = $1;
              }
            ;
            
normcall	: PARENTHESES_OPEN elist PARENTHESES_CLOSE {
                $$ = malloc(sizeof(CallsuffixObj));
                $$->elist = $2;
                $$->method = 0;
                $$->name = NULL;
              }
            ;
            
methodcall	: DOT_DOT ID PARENTHESES_OPEN elist PARENTHESES_CLOSE {
                $$ = malloc(sizeof(CallsuffixObj));
                $$->elist = $4;
                $$->method = 1;
                $$->name = $2;
			  }
			;

tablemake	: BRACKET_OPEN elist BRACKET_CLOSE {
                $$ = make_table($2, 0);
              }
            | BRACKET_OPEN indexed BRACKET_CLOSE {
                $$ = make_table($2, 1);
              }
            ;	

objectdef	: tablemake
            ;
            
elist : elist_plus {
            $$ = $1;
          }
        | /* empty */ {
            $$ = NULL;
          }
        ;
            
elist_plus	: expr {
                $$ = $1;
              }
            | elist_plus COMMA expr {
                $$ = $3;
                $$->next =  $1;
				$1->prev = $$;
              }
            ;
            
indexed	: indexedelem {
            $$ = $1;
          }
        | indexed COMMA indexedelem {
            $$ = $3;
            $$->next = $1;
			$1->prev = $$;
          }
        ;
        
indexedelem	: BLOCK_START expr COLON expr BLOCK_END { 
                $$ = $2;
                $$->index = $4;
              }
            ;
            
block	: BLOCK_START {
              if(!funcflag) {
                  if(++active_scope > scope_depth) scope_depth++;
              }else{
                  funcflag = 0;
              } 
          }
          stmts 
          BLOCK_END {
              hide(active_scope--);  
          }
        ;

funcblockstart  : /* empty*/ {
					new_stop(&return_list);
					infunc_counter++;
                    push_loopcounter(); 
                    loopcounter = 0;
                  }
			    ;
			
funcblockend    : /* empty */ {
					infunc_counter--;
                    loopcounter = pop_loopcounter(); 
                  }
				;


funcname	: ID {
                $$ = $1;
              }
        	| /* empty */ {
                $$ = get_funcname();
              }
            ;

funcprefix	: FUNCTION funcname funcblockstart {
                if(is_unnamed_funcname($2)) {
                    $$ = insert($2, active_scope, yylineno, USERFUNC, NULL, -1);
                    func_entry = $$;
                }else {
                    /* lookup on the currently active scope */
                    $$ = lookup_on_scope($2, active_scope);
                    if(is_lib_func($2)) {
                        yyerror("error: library functions cannot be shadowed");
                    }else if($$) {
                        yyerror("error: symbol already defined");
                    }else{
                        $$ = insert($2, active_scope, yylineno, USERFUNC, NULL, -1);
                        func_entry = $$;	
                    }
                }
                $$->address = currQuad;
                emit(funcstart, NULL, NULL, make_lvalue_expr($$), 0);
            	push_offset();
                scopeSpaceCounter++;
                formalArgOffset = 0;
              }
            ;

funcargs	: PARENTHESES_OPEN {
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
              PARENTHESES_CLOSE {
                scopeSpaceCounter++;
                functionLocalOffset = 0;
              }
            ;

funcbody	: block funcblockend {
                scopeSpaceCounter--;
              }
            ;

funcdef	: funcprefix funcargs funcbody {
            scopeSpaceCounter--;
            $1->totallocals = functionLocalOffset;
            functionLocalOffset = pop_offset();
            $$ = $1;
            emit(funcend, NULL, NULL, make_lvalue_expr($1), 0);
			set_stop_labels(&return_list, currQuad-1);
          }
        ;
        
const	: INTEGER {   
            $$ = newexpr_constnum($1);
          }                 
        | REAL {
            $$ = newexpr_constnum($1);
          }	                 
        | STRING_LITERAL {      
            $$ = newexpr_conststring($1);
          }                
        | NIL {              
            $$ = newexpr(nil_e);
          }                
        | IS_TRUE {
            $$ = newexpr_constbool(1);
          }        
        | IS_FALSE {
            $$ = newexpr_constbool(0);
          }
        ;
        
idlist	: idlist_plus
        | /* empty */
        ;
        
idlist_plus	: ID {
                /* lookup on the currently active scope */
                if(is_lib_func($1)) {
                    yyerror("error: library functions cannot be shadowed");
                }else {
                    insert($1, active_scope, yylineno, FORMALVAR, NULL, -1);
                    if(func_entry) {
                        if(funcargc == max_funcargc) grow_funcargs();
                        funcargs[funcargc++] = strdup($1);
                    }
                }
              }
            | idlist_plus COMMA ID {  
                /* lookup on the currently active scope */
                SymbolTableEntry *entry = lookup_on_scope($3, active_scope);
                if(is_lib_func($3)) {
                    yyerror("error: library functions cannot be shadowed");
                }else if(entry) {
                    yyerror("error: symbol already defined");
                }else {
                    insert($3, active_scope, yylineno, FORMALVAR, NULL, -1);
                    if(func_entry) {
                        if(funcargc == max_funcargc) grow_funcargs();
                        funcargs[funcargc++] = strdup($3);
                    }
                }
              }
            ;
    
    
ifprefix	: IF PARENTHESES_OPEN expr PARENTHESES_CLOSE {
              	emit(if_eq, $3, newexpr_constbool(1), NULL, currQuad + 2);
				$$ = currQuad;
				emit(jump, NULL, NULL, NULL, 0);
        	  }
        	;
         
elseprefix	: ELSE {
				$$ = currQuad;
                emit(jump, NULL, NULL, NULL, 0);
              }
        	;

ifstmt  : ifprefix stmt elseprefix stmt {
			patchlabel($1, $3 + 1);
			patchlabel($3, currQuad);       
          }
        | ifprefix stmt %prec THEN {
			patchlabel($1, currQuad);
          }
        ;

loopstart	: /* empty */ {
				new_stop(&break_list);
				new_stop(&continue_list);
				loopcounter++;
			  }
			;

loopend		: /* empty */ {
				loopcounter--;
			  }
			;

loopstmt	: loopstart stmt loopend
			;
        
whilestart  : WHILE {
				$$ = currQuad;
            }
            ;
           
whilecond	: PARENTHESES_OPEN expr PARENTHESES_CLOSE {
                emit(if_eq, $2, newexpr_constbool(1), NULL, currQuad + 2);
				$$ = currQuad;
                emit(jump, NULL, NULL, NULL, 0);
              }
            ;
            
whilestmt	: whilestart whilecond loopstmt {
                emit(jump, NULL, NULL, NULL, $1);
                patchlabel($2, currQuad);
				set_stop_labels(&break_list, currQuad);
				set_stop_labels(&continue_list, $1);
              }
            ;

N   : /* empty */ {
        $$ = currQuad; 
        emit(jump, NULL, NULL, NULL, 0); 
      }
    ;

M   : /* empty */ {
		$$ = currQuad; 
	  }
    ;

forprefix   : FOR PARENTHESES_OPEN elist SEMICOLON M expr SEMICOLON {
				$$ = malloc(sizeof(ForprefixObj));
				$$->test = $5;
				$$->enter = currQuad;
				emit(if_eq, $6, newexpr_constbool(1), NULL, 0);
		      }
		    ;

forstmt : forprefix N elist PARENTHESES_CLOSE N loopstmt N {
			patchlabel($1->enter, $5 + 1);
			patchlabel($2, currQuad);
			patchlabel($5, $1->test);
			patchlabel($7, $2 + 1);
			set_stop_labels(&break_list, currQuad);
			set_stop_labels(&continue_list, $2 + 1);
          } 
        ;
        
returnstmt	: RETURN expr SEMICOLON {
				if(infunc_counter <= 0)  yyerror("error: return out of function block");
                emit(ret, NULL, NULL, $2, 0);
              }
            | RETURN SEMICOLON {
				if(infunc_counter <= 0)  yyerror("error: return out of function block");
            	emit(ret, NULL, NULL, NULL, 0);
              }
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
		//alpha_yylex_test();
		intermediate_init();
		symbol_table_init();
		yyparse();
		print_symbol_table();
		print_scope_lists();
	}else { 
		/* RUN PARSER */
		symbol_table_init();
		intermediate_init();
		target_init();
		yyparse();
		// Generate code
		mkdir("output", 0777);
		print_quads("output/quads.i");
		generate_instructions();
		print_instructions("output/instructions.t");
		print_binary_file("output/truetext.avm", "output/binary.avm");
	}

    return 0;
    
}