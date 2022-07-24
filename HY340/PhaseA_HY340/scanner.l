%option noyywrap
%option yylineno

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9_]*
INLINE_COMMENT "//".*
OPERATOR "="|"+"|"-"|"*"|"/"|"%"|"=="|"!="|"++"|"--"|">"|"<"|">="|"<="
KEYWORD "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"and"|"not"|"or"|"local"|"true"|"false"|"nil"
PUNCTUATION "{"|"}"|"["|"]"|"("|")"|";"|","|":"|"::"|"."|".."
WHITESPACE [ \t\n\r]

%{

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define YY_DECL int alpha_yylex(void* yylval)
#define MAX_TOKEN_SIZE 1024
#define NEW_TOKEN(token)							\
	token = malloc(sizeof(alpha_token_t)); 			\
	token->lineno = 0; token->tokenno = 0;			\
	token->content = NULL; token->category = NULL; 	\
	token->type = NULL; token->next = NULL;
#define NON_CONTINUABLE -1
#define KNOWN 1
#define UNKNOWN 2
#define LISTLESS 3

int comment_nesting = 0;
int tokenno = 0;
char *buffer;
int current_size = MAX_TOKEN_SIZE * sizeof(char);
char *buffer_type;

typedef struct alpha_token {
    int	lineno;
    int	tokenno;
    char *content;
    char *category;
    char *type;
	struct alpha_token *next;
}alpha_token_t;

void insert_token(alpha_token_t *token, int lineno, int tokenno, char *content, char *category, char *type) {
	
	alpha_token_t *new_token, *tmp;

	if(token->tokenno == 0) {
		token->lineno = lineno;
		token->tokenno = tokenno;
		token->content = malloc((strlen(content) + 1) * sizeof(char));
		token->content = strcpy(token->content, content);
		token->category = category;
		token->type = type;
		token->next = NULL;
		return;
	}

	NEW_TOKEN(new_token);
	new_token->lineno = lineno;
	new_token->tokenno = tokenno;
	new_token->content = malloc((strlen(content) + 1) * sizeof(char));
	new_token->content = strcpy(new_token->content, content);
	new_token->category = category;
	new_token->type = type;
	new_token->next = NULL;

	tmp = token;
	while(tmp->next){
		tmp = tmp->next;
	}
	tmp->next = new_token;

	return;

}

alpha_token_t *insert_token_list(alpha_token_t *token_list, alpha_token_t *token) {

	alpha_token_t *tmp;

	if(token_list->tokenno == 0) {
		tmp = token_list;
		token_list = token;
		free(tmp);
		return token_list;	
	}

	tmp = token_list;
	while(tmp->next){
		tmp = tmp->next;
	}
	tmp->next = token;

	return token_list;

}

void print_tokens(alpha_token_t *token) {

	alpha_token_t *atoken = token;
	while(atoken != NULL) {
		printf("%d: #%d  %s  %s  %s\n", atoken->lineno,
				atoken->tokenno, atoken->content,
        		atoken->category, atoken->type);
		atoken = atoken->next;
	}

}

void free_token_list(alpha_token_t *token) {

	alpha_token_t *tmp;
	
	while(token != NULL) {
		tmp = token;
		token = token->next;
		free(tmp);	
	}

}

int strmerge(char *buf1, char *buf2, int max_size) {

	int size1 = strlen(buf1);
	int size2 = strlen(buf2);
	char *tmp;

	while(size1 + size2 >= max_size) {
		max_size = max_size * 2;
		tmp = realloc(buf1, max_size);
		if(tmp != NULL) {
			buf1 = tmp;		
		}else {
			printf("Failed to allocate memory\n");
			exit(0);	
		}
	}
	strcat(buf1, buf2);

	return max_size;

}

%}

%x COMMENT
%x STRING

%%

"/*"		{ 
				BEGIN(COMMENT);
				tokenno++;
				insert_token(yylval, yylineno, tokenno, "/*...*/", "COMMENT", "MULTILINE");
			}
<COMMENT>{
	"/*"		{ 
					++comment_nesting;	
					tokenno++;
					insert_token(yylval, yylineno, tokenno, "/*...*/", "COMMENT", "NESTED_MULTILINE");
				}
	"*"+"/"		{
					if (comment_nesting) {
						--comment_nesting;
					} else {
						BEGIN(INITIAL);
						return KNOWN;
					}
				}
	"*"+		{}
  	[^/*\n]+	{}
  	[/]			{}
  	\n			{}
	<<EOF>>		{
					free_token_list(((alpha_token_t *)yylval)->next);
					((alpha_token_t *)yylval)->next = NULL;
					((alpha_token_t *)yylval)->content = "/*...\n<EOF>";
					((alpha_token_t *)yylval)->category = "COMMENT";
					((alpha_token_t *)yylval)->type = "UNTERMINATED_COMMENT";
					return NON_CONTINUABLE;
				}
}

\"				{
					BEGIN(STRING);
					buffer_type = "CHAR*";
					buffer = malloc(current_size);
					buffer[0] = '\0';
					current_size = strmerge(buffer, "\"", current_size);
				}
<STRING>{
	[^\\\"]*	{ current_size = strmerge(buffer, yytext, current_size); }
	\\n         { current_size = strmerge(buffer, "\n", current_size); }
	\\t         { current_size = strmerge(buffer, "\t", current_size); }
	\\\"		{ current_size = strmerge(buffer, "\"", current_size); }
	\\\'     	{ current_size = strmerge(buffer, "\'", current_size); }
	\\\\		{ current_size = strmerge(buffer, "\\", current_size); }
	\"      	{
					tokenno++;
					BEGIN(INITIAL);
					current_size = strmerge(buffer, "\"", current_size);
					insert_token(yylval, yylineno, tokenno, buffer, "STRING", buffer_type);
					return KNOWN;
				}
	<<EOF>>		{
					tokenno++;
					current_size = strmerge(buffer, "<EOF>", current_size);
					insert_token(yylval, yylineno, tokenno, buffer, "STRING", "UNTERMINATED_STRING");
					return NON_CONTINUABLE;
				}
	\\.         {
					current_size = strmerge(buffer, yytext, current_size);
					buffer_type = "CONTAINING_UNKNOWN_ESCAPE_CHARACTER";
				}
}

{KEYWORD}   {
				tokenno++;
				insert_token(yylval, yylineno, tokenno, yytext, "KEYWORD", "ENUMERATED");
				return KNOWN;
			}

{OPERATOR}  {
				tokenno++;
				insert_token(yylval, yylineno, tokenno, yytext, "OPERATOR", "NO_TYPE");
				return KNOWN;
			}

{DIGIT}+    {
				tokenno++;
				insert_token(yylval, yylineno, tokenno, yytext, "INTEGER", "INT");
				return KNOWN;
			}

{DIGIT}+"."{DIGIT}+ {
						tokenno++;
						insert_token(yylval, yylineno, tokenno, yytext, "REAL", "FLOAT");
						return KNOWN;
					}

{PUNCTUATION}   {
					tokenno++;
					insert_token(yylval, yylineno, tokenno, yytext, "PUNCTUATION", "NO_TYPE");
					return KNOWN;
				}

{ID}    {
			tokenno++;
			insert_token(yylval, yylineno, tokenno, yytext, "ID", "CHAR*");
			return KNOWN;
		}

{INLINE_COMMENT}	{
						tokenno++;
						insert_token(yylval, yylineno, tokenno, "//...", "COMMENT", "INLINE");
						return KNOWN;
					}

{WHITESPACE}+	{ return LISTLESS; }

.   {
		tokenno++;
		insert_token(yylval, yylineno, tokenno, yytext, "UNKNOWN", "NO_TYPE");
		return UNKNOWN; 
	}

%%

int main(int argc,char **argv) {

	alpha_token_t *tmp_token, *token_list;
	NEW_TOKEN(token_list);
	NEW_TOKEN(tmp_token);
	int x;

   	++argv, --argc; /* skipping over program name */
    switch(argc) {
        case 0:
            yyin = stdin;
            yyout = stdout;
            break;
        case 1:
            yyin = fopen(argv[0], "r");
            yyout = stdout;
            break;
        case 2:
            yyin = fopen(argv[0], "r");
            yyout = fopen(argv[1], "w");
            break;
        default:
            assert(0);
    }

	while(x = alpha_yylex(tmp_token)) {
		if(x != LISTLESS) {
			token_list = insert_token_list(token_list, tmp_token);
			NEW_TOKEN(tmp_token);
		}
		if(x == NON_CONTINUABLE) break;
	}

	print_tokens(token_list);
	free_token_list(token_list);

    return 0;

}
