/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    STRING_LITERAL = 259,
    INTEGER = 260,
    REAL = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    AND = 270,
    NOT = 271,
    OR = 272,
    LOCAL = 273,
    IS_TRUE = 274,
    IS_FALSE = 275,
    NIL = 276,
    ASSIGN = 277,
    PLUS = 278,
    MINUS = 279,
    STAR = 280,
    SLASH = 281,
    MOD = 282,
    EQUAL = 283,
    UNEQUAL = 284,
    PLUS_PLUS = 285,
    MINUS_MINUS = 286,
    GREATER = 287,
    LESSER = 288,
    GREATER_OR_EQUAL = 289,
    LESSER_OR_EQUAL = 290,
    BLOCK_START = 291,
    BLOCK_END = 292,
    BRACKET_OPEN = 293,
    BRACKET_CLOSE = 294,
    PARENTHESES_OPEN = 295,
    PARENTHESES_CLOSE = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    SCOPE = 300,
    DOT = 301,
    DOT_DOT = 302,
    UNARY_MINUS = 303,
    THEN = 304
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING_LITERAL 259
#define INTEGER 260
#define REAL 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define AND 270
#define NOT 271
#define OR 272
#define LOCAL 273
#define IS_TRUE 274
#define IS_FALSE 275
#define NIL 276
#define ASSIGN 277
#define PLUS 278
#define MINUS 279
#define STAR 280
#define SLASH 281
#define MOD 282
#define EQUAL 283
#define UNEQUAL 284
#define PLUS_PLUS 285
#define MINUS_MINUS 286
#define GREATER 287
#define LESSER 288
#define GREATER_OR_EQUAL 289
#define LESSER_OR_EQUAL 290
#define BLOCK_START 291
#define BLOCK_END 292
#define BRACKET_OPEN 293
#define BRACKET_CLOSE 294
#define PARENTHESES_OPEN 295
#define PARENTHESES_CLOSE 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define SCOPE 300
#define DOT 301
#define DOT_DOT 302
#define UNARY_MINUS 303
#define THEN 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 26 "parser.y" /* yacc.c:1909  */

    char				*sval;
    int					ival;
    double				rval;
    SymbolTableEntry	*eval;
    Expr 				*xval;
    CallsuffixObj 		*cval;
	ForprefixObj 		*fval;

#line 162 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
