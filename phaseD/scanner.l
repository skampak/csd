%{

	#include "intermediate.h"
	#include "parser.h"

	#define YY_DECL	int alpha_yylex()
	#define MAX_TOKEN_SIZE	1024
	#define SAVE_TOKEN(T)	(yylval.ival = T)
	#define SAVE_STRING(S)	(yylval.sval = S)
	#define SAVE_INTEGER(I)	(yylval.ival = I)
	#define SAVE_REAL(R)	(yylval.rval = R)
	#define LTEST(x) fprintf(stderr, "LEXER(%d)\n", x);

	YY_DECL; /* make alpha_yylex visible to functions inside scanner.l */

	int comment_nesting = 0;
	int current_size = 0;
	char *buffer = NULL;

	void alpha_yylex_test() {

		int type = 0;
		int tokenno = 0;
		char *category;
		char *content;

		while((type = alpha_yylex())) {
			content = yytext;
			switch(type) {
				case ID: 
					category = "ID";
					break;
				case STRING_LITERAL: 
					category = "STRING";
					content = buffer;
					break;
				case INTEGER: 
					category = "INTEGER";
					break;
				case REAL: 
					category = "REAL";
					break;
				case IF: 
					category = "IF";
					break;
				case ELSE: 
					category = "ELSE";
					break;
				case WHILE: 
					category = "WHILE";
					break;
				case FOR: 
					category = "FOR";
					break;
				case FUNCTION: 
					category = "FUNCTION";
					break;
				case RETURN: 
					category = "RETURN";
					break;
				case BREAK: 
					category = "BREAK";
					break;
				case CONTINUE: 
					category = "CONTINUE";
					break;
				case AND: 
					category = "AND";
					break;
				case OR: 
					category = "OR";
					break;
				case LOCAL: 
					category = "LOCAL";
					break;
				case IS_TRUE: 
					category = "TRUE";
					break;
				case IS_FALSE: 
					category = "FALSE";
					break;
				case NIL: 
					category = "NIL";
					break;
				case ASSIGN: 
					category = "ASSIGN";
					break;
				case PLUS: 
					category = "PLUS";
					break;
				case MINUS: 
					category = "MINUS";
					break;
				case STAR: 
					category = "STAR";
					break;
				case SLASH: 
					category = "SLASH";
					break;
				case MOD: 
					category = "MOD";
					break;
				case EQUAL: 
					category = "EQUAL";
					break;
				case UNEQUAL: 
					category = "UNEQUAL";
					break;
				case PLUS_PLUS: 
					category = "PLUS_PLUS";
					break;
				case MINUS_MINUS: 
					category = "MINUS_MINUS";
					break;
				case GREATER: 
					category = "GREATER";
					break;
				case LESSER: 
					category = "LESSER";
					break;
				case GREATER_OR_EQUAL: 
					category = "GREATER_OR_EQUAL";
					break;
				case LESSER_OR_EQUAL: 
					category = "LESSER_OR_EQUAL";
					break;
				case BLOCK_START: 
					category = "BLOCK_START";
					break;
				case BLOCK_END: 
					category = "BLOCK_END";
					break;
				case BRACKET_OPEN: 
					category = "BRACKET_OPEN";
					break;
				case BRACKET_CLOSE: 
					category = "BRACKET_CLOSE";
					break;
				case PARENTHESES_OPEN: 
					category = "PARENTHESES_OPEN";
					break;
				case PARENTHESES_CLOSE: 
					category = "PARENTHESES_CLOSE";
					break;
				case SEMICOLON: 
					category = "SEMICOLON";
					break;
				case COMMA: 
					category = "COMMA";
					break;
				case COLON: 
					category = "COLON";
					break;
				case SCOPE: 
					category = "SCOPE";
					break;
				case DOT: 
					category = "DOT";
					break;
				case DOT_DOT: 
					category = "DOT_DOT";
					break;
				case UNARY_MINUS: 
					category = "UNARY_MINUS";
					break;
				case THEN: 
					category = "THEN";
					break;
				default:
					assert(0);
				
			}
			printf("%d: #%d  %s  %s\n", yylineno, ++tokenno, content, category);
		}
	
		return;
	
	}

	void yyerror(char* providedMessage) {
	
		if(strstr(providedMessage, "EOF") != NULL) {
			fprintf(stderr, "%s: at line %d\n", providedMessage, yylineno);
		}else {
			fprintf(stderr, "%s: at line %d [ token: %s ]\n", providedMessage, yylineno, yytext);
		}

		error_flag = 1;
		
		return;
	
	}

	int strmerge(char *buf1, char *buf2, int max_size) {

		int size1 = strlen(buf1);
		int size2 = strlen(buf2);
		char *tmp;

		while(size1 + size2 >= max_size) {
			max_size = max_size * 2;
		}
		tmp = realloc(buf1, max_size);
		if(tmp != NULL) {
			buf1 = tmp;		
		}else {
			fprintf(stderr, "Failed to allocate memory\n");
			exit(EXIT_FAILURE);	
		}
		strcat(buf1, buf2);

		return max_size;

	}

%}

%option noyywrap
%option yylineno

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9_]*
IL_COMMENT "//".*
WHITESPACE [ \t\n\r]

%x ML_COMMENT
%x STRING

%%

"/*"		{
				comment_nesting = 0;
				BEGIN(ML_COMMENT); 
			}
<ML_COMMENT>{
	"/*"		{ ++comment_nesting; }
	"*"+"/"		{
					if (comment_nesting) {
						--comment_nesting;
					} else {
						BEGIN(INITIAL);
					}
				}
	"*"+		{}
  	[^/*\n]+	{}
  	[/]			{}
  	\n			{}
	<<EOF>>		{ 
					yyerror("lexical error: EOF in multiline comment");
					exit(EXIT_FAILURE); 
				}
}

\"				{
					BEGIN(STRING);
					current_size = MAX_TOKEN_SIZE * sizeof(char);
					buffer = malloc(current_size);
					buffer[0] = '\0';
				}
<STRING>{
	[^\\\"]*	{ current_size = strmerge(buffer, yytext, current_size); }
	\\n         { current_size = strmerge(buffer, "\n", current_size); }
	\\t         { current_size = strmerge(buffer, "\t", current_size); }
	\\\"		{ current_size = strmerge(buffer, "\"", current_size); }
	\\\'     	{ current_size = strmerge(buffer, "\'", current_size); }
	\\\\		{ current_size = strmerge(buffer, "\\", current_size); }
	\"      	{
					BEGIN(INITIAL);
					SAVE_STRING(buffer);
					return STRING_LITERAL;
				}
	<<EOF>>		{ 
					yyerror("lexical error: EOF in string"); 
					exit(EXIT_FAILURE); 
				}
	\\.         { 
					yyerror("lexical error: unknown escape character in string");
					current_size = strmerge(buffer, yytext, current_size); 
				}
}

"if"		{ return SAVE_TOKEN(IF); }
"else"		{ return SAVE_TOKEN(ELSE); }
"while"		{ return SAVE_TOKEN(WHILE); }
"for"		{ return SAVE_TOKEN(FOR); }
"function"	{ return SAVE_TOKEN(FUNCTION); }
"return"	{ return SAVE_TOKEN(RETURN); }
"break"		{ return SAVE_TOKEN(BREAK); }
"continue"	{ return SAVE_TOKEN(CONTINUE); }
"and"		{ return SAVE_TOKEN(AND); }
"not"		{ return SAVE_TOKEN(NOT); }
"or"		{ return SAVE_TOKEN(OR); }
"local"		{ return SAVE_TOKEN(LOCAL); }
"true"		{ return SAVE_TOKEN(IS_TRUE); }
"false"		{ return SAVE_TOKEN(IS_FALSE); }
"nil"		{ return SAVE_TOKEN(NIL); }

"="			{ return SAVE_TOKEN(ASSIGN); }
"+"			{ return SAVE_TOKEN(PLUS); }
"-"			{ return SAVE_TOKEN(MINUS); }
"*"			{ return SAVE_TOKEN(STAR); }
"/"			{ return SAVE_TOKEN(SLASH); }
"%"			{ return SAVE_TOKEN(MOD); }
"=="		{ return SAVE_TOKEN(EQUAL); }
"!="		{ return SAVE_TOKEN(UNEQUAL); }
"++"		{ return SAVE_TOKEN(PLUS_PLUS); }
"--"		{ return SAVE_TOKEN(MINUS_MINUS); }
">"			{ return SAVE_TOKEN(GREATER); }
"<"			{ return SAVE_TOKEN(LESSER); }
">="		{ return SAVE_TOKEN(GREATER_OR_EQUAL); }
"<="		{ return SAVE_TOKEN(LESSER_OR_EQUAL); }

"{"			{ return SAVE_TOKEN(BLOCK_START); }
"}"			{ return SAVE_TOKEN(BLOCK_END); }
"["			{ return SAVE_TOKEN(BRACKET_OPEN); }
"]"			{ return SAVE_TOKEN(BRACKET_CLOSE); }
"("			{ return SAVE_TOKEN(PARENTHESES_OPEN); }
")"			{ return SAVE_TOKEN(PARENTHESES_CLOSE); }
";"			{ return SAVE_TOKEN(SEMICOLON); }
","			{ return SAVE_TOKEN(COMMA); }
":"			{ return SAVE_TOKEN(COLON); }
"::"		{ return SAVE_TOKEN(SCOPE); }
"."			{ return SAVE_TOKEN(DOT); }
".."		{ return SAVE_TOKEN(DOT_DOT); }

{DIGIT}+    {
				SAVE_INTEGER(atoi(yytext));
				return INTEGER;
			}

{DIGIT}+"."{DIGIT}+ {
						SAVE_REAL(atof(yytext));
						return REAL;
					}

{ID}    {
			SAVE_STRING(strdup(yytext));
			return ID;
		}

{IL_COMMENT}	{}

{WHITESPACE}+	{}

.   { yyerror("lexical error: unknown token"); }
