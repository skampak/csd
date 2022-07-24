/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


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
    

#line 89 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
#line 26 "parser.y" /* yacc.c:355  */

    char				*sval;
    int					ival;
    double				rval;
    SymbolTableEntry	*eval;
    Expr 				*xval;
    CallsuffixObj 		*cval;
	ForprefixObj 		*fval;

#line 237 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 252 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   575

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  189

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    80,    83,    86,    87,    88,    89,    90,
      94,   102,   110,   111,   112,   115,   116,   119,   122,   125,
     128,   131,   134,   137,   140,   143,   146,   149,   152,   155,
     160,   163,   166,   171,   177,   183,   189,   195,   200,   208,
     211,   212,   213,   217,   222,   233,   245,   255,   258,   261,
     269,   270,   271,   274,   277,   289,   296,   299,   304,   312,
     320,   323,   328,   331,   334,   339,   342,   349,   352,   359,
     365,   365,   378,   386,   393,   396,   401,   425,   429,   425,
     442,   447,   457,   460,   463,   466,   469,   472,   477,   478,
     481,   493,   511,   518,   524,   528,   533,   540,   545,   548,
     553,   560,   568,   574,   579,   587,   597,   601
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING_LITERAL", "INTEGER",
  "REAL", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "IS_TRUE", "IS_FALSE", "NIL",
  "ASSIGN", "PLUS", "MINUS", "STAR", "SLASH", "MOD", "EQUAL", "UNEQUAL",
  "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESSER", "GREATER_OR_EQUAL",
  "LESSER_OR_EQUAL", "BLOCK_START", "BLOCK_END", "BRACKET_OPEN",
  "BRACKET_CLOSE", "PARENTHESES_OPEN", "PARENTHESES_CLOSE", "SEMICOLON",
  "COMMA", "COLON", "SCOPE", "DOT", "DOT_DOT", "UNARY_MINUS", "THEN",
  "$accept", "program", "stmts", "stmt", "expr", "term", "assignexpr",
  "primary", "lvalue", "tableitem", "member", "call", "callsuffix",
  "normcall", "methodcall", "tablemake", "objectdef", "elist",
  "elist_plus", "indexed", "indexedelem", "block", "$@1", "funcblockstart",
  "funcblockend", "funcname", "funcprefix", "funcargs", "$@2", "$@3",
  "funcbody", "funcdef", "const", "idlist", "idlist_plus", "ifprefix",
  "elseprefix", "ifstmt", "loopstart", "loopend", "loopstmt", "whilestart",
  "whilecond", "whilestmt", "N", "M", "forprefix", "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -163

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-163)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -163,     7,   155,  -163,  -163,  -163,  -163,  -163,   -29,  -163,
     -23,    23,   198,    -4,     0,   251,    42,  -163,  -163,  -163,
     251,    25,    25,  -163,    16,   228,  -163,    50,  -163,   297,
    -163,  -163,  -163,   410,  -163,  -163,   -13,  -163,  -163,  -163,
      15,  -163,  -163,   155,  -163,    17,  -163,  -163,  -163,  -163,
     251,   251,  -163,  -163,  -163,   318,  -163,  -163,  -163,  -163,
    -163,    48,   -32,   -13,   -32,  -163,   251,   499,    21,    19,
     -27,  -163,   360,    22,  -163,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,  -163,   251,
    -163,  -163,   251,   251,    63,    64,  -163,  -163,  -163,   251,
     251,    65,  -163,    33,    78,   251,  -163,   251,   381,    29,
    -163,  -163,    31,   112,   275,  -163,   251,  -163,    52,  -163,
      49,   527,   514,     4,     4,  -163,  -163,  -163,   540,   540,
     253,   253,   253,   253,   499,   436,    51,  -163,    53,   457,
      54,  -163,    88,  -163,  -163,  -163,   155,   402,   155,  -163,
      55,  -163,  -163,    49,  -163,   251,   499,  -163,   251,  -163,
    -163,   251,  -163,  -163,  -163,  -163,    56,  -163,  -163,  -163,
    -163,  -163,   251,   478,    57,    59,    60,    91,  -163,  -163,
     339,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    44,    84,    82,    83,     0,    99,
       0,    75,     0,     0,     0,     0,     0,    86,    87,    85,
       0,     0,     0,    70,    64,     0,    14,     0,     3,     0,
      29,    15,    37,    39,    50,    47,    40,    62,    41,    12,
       0,    13,    43,     0,     6,     0,     7,   102,     8,     9,
       0,    64,    74,    72,   107,     0,    10,    11,    32,    45,
      31,     0,    33,     0,    35,     4,     0,    65,     0,    63,
       0,    67,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     0,
      34,    36,     0,    64,     0,     0,    54,    56,    57,     0,
      64,     0,    77,     0,    95,     0,    96,    64,     0,     0,
      76,   106,     0,     0,     0,    60,     0,    61,     0,    30,
      42,    27,    28,    16,    17,    18,    19,    20,    25,    26,
      21,    23,    22,    24,    38,     0,     0,    48,     0,     0,
       0,    51,    89,    73,    81,    93,     0,     0,     0,   101,
       0,    92,   103,     0,    71,     0,    66,    68,    64,    49,
      58,    64,    52,    53,    90,    78,    88,    80,    94,   100,
      97,   102,     0,     0,     0,     0,     0,     0,    98,    96,
       0,    69,    55,    59,    79,    91,   102,   104,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,  -163,    37,   -42,    -2,  -163,  -163,  -163,   -17,  -163,
    -163,    28,  -163,  -163,  -163,  -163,  -163,   -49,  -163,  -163,
     -11,     2,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,   -22,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
     -71,  -163,  -163,  -163,  -162,  -163,  -163,  -163,  -163
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    67,    30,    31,    32,    33,    34,
      35,    36,    96,    97,    98,    37,    38,    68,    69,    70,
      71,    39,    65,   110,   167,    53,    40,   103,   142,   176,
     144,    41,    42,   165,   166,    43,   146,    44,   148,   178,
     149,    45,   106,    46,   107,   172,    47,    48,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   104,   109,    73,    62,    64,    92,     3,    93,   179,
      55,    50,   117,    58,    94,    95,   118,    51,    60,     4,
       5,     6,     7,    72,   188,    99,    52,   100,     4,    79,
      80,    81,    15,   101,    16,    17,    18,    19,    56,   112,
      20,    29,    57,    16,   136,    59,    21,    22,   108,    63,
      63,   140,    66,    74,    24,   102,    25,   105,   150,    11,
     115,    27,   116,   120,   114,    61,   137,   138,   141,    23,
      27,   152,   153,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   145,   134,    66,   158,
     135,   164,   160,   161,   185,   163,   171,   139,   182,   177,
     183,   184,   113,   147,   168,   143,   170,   157,   186,   174,
       0,    29,   175,     0,   156,     4,     5,     6,     7,     8,
       0,     9,    10,    11,    12,    13,    14,     0,    15,     0,
      16,    17,    18,    19,     0,     0,    20,     0,     0,     0,
       0,     0,    21,    22,    29,     0,    29,     0,    23,   154,
      24,     0,    25,   173,    26,     0,     0,    27,     4,     5,
       6,     7,     8,     0,     9,    10,    11,    12,    13,    14,
     180,    15,     0,    16,    17,    18,    19,     0,     0,    20,
       0,     0,     0,     0,     0,    21,    22,     0,     0,     0,
       0,    23,     0,    24,     0,    25,     0,    26,     0,     0,
      27,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    16,    17,    18,    19,
       0,     0,    20,     0,     0,     0,     0,     0,    21,    22,
       0,     4,     5,     6,     7,     0,    24,     0,    25,    11,
      54,     0,     0,    27,    15,     0,    16,    17,    18,    19,
       0,     0,    20,     0,     4,     5,     6,     7,    21,    22,
       0,     0,     0,     0,     0,     0,    24,    15,    25,    16,
      17,    18,    19,    27,     0,    20,    77,    78,    79,    80,
      81,    21,    22,     0,     0,    -1,    -1,    -1,    -1,    24,
      75,    25,    76,     0,     0,     0,    27,     0,    77,    78,
      79,    80,    81,    82,    83,     0,     0,    84,    85,    86,
      87,     0,    75,     0,    76,     0,     0,     0,     0,   155,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87,    75,     0,    76,     0,     0,     0,    88,
       0,    77,    78,    79,    80,    81,    82,    83,     0,     0,
      84,    85,    86,    87,    75,     0,    76,     0,     0,     0,
     111,     0,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    84,    85,    86,    87,    75,     0,    76,     0,     0,
       0,   187,     0,    77,    78,    79,    80,    81,    82,    83,
       0,     0,    84,    85,    86,    87,    75,     0,    76,     0,
       0,   119,     0,     0,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    75,     0,    76,
       0,     0,   151,     0,     0,    77,    78,    79,    80,    81,
      82,    83,    89,     0,    84,    85,    86,    87,     0,     0,
      90,    91,     0,   169,     0,     0,     0,     0,    92,     0,
      93,    75,     0,    76,     0,     0,    94,    95,     0,    77,
      78,    79,    80,    81,    82,    83,     0,     0,    84,    85,
      86,    87,    75,     0,    76,   159,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87,    75,     0,    76,   162,     0,     0,     0,
       0,    77,    78,    79,    80,    81,    82,    83,     0,     0,
      84,    85,    86,    87,    75,   181,    76,     0,     0,     0,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    75,
       0,    84,    85,    86,    87,     0,     0,    77,    78,    79,
      80,    81,    82,    83,     0,     0,    84,    85,    86,    87,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87,    77,    78,    79,    80,    81,    -1,    -1,
       0,     0,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       2,    43,    51,    25,    21,    22,    38,     0,    40,   171,
      12,    40,    39,    15,    46,    47,    43,    40,    20,     3,
       4,     5,     6,    25,   186,    38,     3,    40,     3,    25,
      26,    27,    16,    46,    18,    19,    20,    21,    42,    61,
      24,    43,    42,    18,    93,     3,    30,    31,    50,    21,
      22,   100,    36,     3,    38,    40,    40,    40,   107,    11,
      39,    45,    43,    41,    66,    40,     3,     3,     3,    36,
      45,    42,    41,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     8,    89,    36,    40,
      92,     3,    41,    40,     3,    41,    41,    99,    41,    43,
      41,    41,    65,   105,   146,   103,   148,   118,   179,   158,
      -1,   113,   161,    -1,   116,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    14,    -1,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,   146,    -1,   148,    -1,    36,    37,
      38,    -1,    40,   155,    42,    -1,    -1,    45,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    14,
     172,    16,    -1,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,
      -1,    36,    -1,    38,    -1,    40,    -1,    42,    -1,    -1,
      45,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,     3,     4,     5,     6,    -1,    38,    -1,    40,    11,
      42,    -1,    -1,    45,    16,    -1,    18,    19,    20,    21,
      -1,    -1,    24,    -1,     3,     4,     5,     6,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    16,    40,    18,
      19,    20,    21,    45,    -1,    24,    23,    24,    25,    26,
      27,    30,    31,    -1,    -1,    32,    33,    34,    35,    38,
      15,    40,    17,    -1,    -1,    -1,    45,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    44,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,    42,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,
      42,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    -1,    17,    -1,    -1,
      -1,    42,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    15,    -1,    17,    -1,
      -1,    41,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    -1,    17,
      -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    22,    -1,    32,    33,    34,    35,    -1,    -1,
      30,    31,    -1,    41,    -1,    -1,    -1,    -1,    38,    -1,
      40,    15,    -1,    17,    -1,    -1,    46,    47,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    -1,    17,    39,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    39,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    37,    17,    -1,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    15,
      -1,    32,    33,    34,    35,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    52,     0,     3,     4,     5,     6,     7,     9,
      10,    11,    12,    13,    14,    16,    18,    19,    20,    21,
      24,    30,    31,    36,    38,    40,    42,    45,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    65,    66,    71,
      76,    81,    82,    85,    87,    91,    93,    96,    97,    98,
      40,    40,     3,    75,    42,    54,    42,    42,    54,     3,
      54,    40,    58,    61,    58,    72,    36,    54,    67,    68,
      69,    70,    54,    81,     3,    15,    17,    23,    24,    25,
      26,    27,    28,    29,    32,    33,    34,    35,    42,    22,
      30,    31,    38,    40,    46,    47,    62,    63,    64,    38,
      40,    46,    40,    77,    53,    40,    92,    94,    54,    67,
      73,    42,    81,    52,    54,    39,    43,    39,    43,    41,
      41,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    67,     3,     3,    54,
      67,     3,    78,    71,    80,     8,    86,    54,    88,    90,
      67,    41,    42,    41,    37,    44,    54,    70,    40,    39,
      41,    40,    39,    41,     3,    83,    84,    74,    53,    41,
      53,    41,    95,    54,    67,    67,    79,    43,    89,    94,
      54,    37,    41,    41,    41,     3,    90,    42,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    57,
      57,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    61,    61,    61,    62,    62,    63,    64,
      65,    65,    66,    67,    67,    68,    68,    69,    69,    70,
      72,    71,    73,    74,    75,    75,    76,    78,    79,    77,
      80,    81,    82,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    86,    87,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       1,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       3,     3,     1,     1,     0,     1,     3,     1,     3,     5,
       0,     4,     0,     0,     1,     0,     3,     0,     0,     5,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     4,     1,     4,     2,     0,     0,     3,     1,
       3,     3,     0,     0,     7,     7,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 80 "parser.y" /* yacc.c:1646  */
    {
			tmpnum = 0;
		  }
#line 1548 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 90 "parser.y" /* yacc.c:1646  */
    {
			add_stop(&return_list);
			emit(jump, NULL, NULL, NULL, 0);
		  }
#line 1557 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 94 "parser.y" /* yacc.c:1646  */
    {
			if(loopcounter > 0){
				add_stop(&break_list);
				emit(jump, NULL, NULL, NULL, 0);
			}else {
				yyerror("error: break out of loop block");
			}
          }
#line 1570 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 102 "parser.y" /* yacc.c:1646  */
    {
			if(loopcounter > 0){
				add_stop(&continue_list);
				emit(jump, NULL, NULL, NULL, 0);
			}else {
				yyerror("error: continue out of loop block");
			}
          }
#line 1583 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 116 "parser.y" /* yacc.c:1646  */
    {
			(yyval.xval) = make_arithop(add, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1591 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 119 "parser.y" /* yacc.c:1646  */
    {  
            (yyval.xval) = make_arithop(sub, (yyvsp[-2].xval), (yyvsp[0].xval));		
          }
#line 1599 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 122 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_arithop(mul, (yyvsp[-2].xval), (yyvsp[0].xval)); 
          }
#line 1607 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 125 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_arithop(divide, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1615 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 128 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_arithop(mod, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1623 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 131 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_greater, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1631 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 134 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_greatereq, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1639 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 137 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_less, (yyvsp[-2].xval), (yyvsp[0].xval)); 
          }
#line 1647 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_lesseq, (yyvsp[-2].xval), (yyvsp[0].xval)); 
          }
#line 1655 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 143 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_eq, (yyvsp[-2].xval), (yyvsp[0].xval)); 
          }
#line 1663 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 146 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_relop(if_noteq, (yyvsp[-2].xval), (yyvsp[0].xval)); 
          }
#line 1671 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 149 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = make_boolop(and, (yyvsp[-2].xval), (yyvsp[0].xval));
          }
#line 1679 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 152 "parser.y" /* yacc.c:1646  */
    { 
            (yyval.xval) = make_boolop(or, (yyvsp[-2].xval), (yyvsp[0].xval));                           
          }
#line 1687 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 155 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval);
          }
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 160 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[-1].xval);
          }
#line 1703 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 163 "parser.y" /* yacc.c:1646  */
    {
			(yyval.xval) = make_arithop(mul, newexpr_constnum(-1), (yyvsp[0].xval));
          }
#line 1711 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 166 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = newexpr(boolexpr_e);
            (yyval.xval)->sym = newtmp();
            emit(not, (yyvsp[0].xval), NULL, (yyval.xval), 0);
          }
#line 1721 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 171 "parser.y" /* yacc.c:1646  */
    {
			if(get_primitive_type((yyvsp[0].xval)->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            (yyval.xval) = make_opterm(add, (yyvsp[0].xval)); 
          }
#line 1732 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 177 "parser.y" /* yacc.c:1646  */
    {
			if(get_primitive_type((yyvsp[-1].xval)->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            (yyval.xval) = make_termop(add, (yyvsp[-1].xval));
          }
#line 1743 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 183 "parser.y" /* yacc.c:1646  */
    {
			if(get_primitive_type((yyvsp[0].xval)->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            (yyval.xval) = make_opterm(sub, (yyvsp[0].xval));
          }
#line 1754 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 189 "parser.y" /* yacc.c:1646  */
    {
			if(get_primitive_type((yyvsp[-1].xval)->sym->type) != VAR_S) {
				yyerror("error: functions cannot be used as lvalue");
			}
            (yyval.xval) = make_termop(sub, (yyvsp[-1].xval));
          }
#line 1765 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval);
          }
#line 1773 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 200 "parser.y" /* yacc.c:1646  */
    {
				if(get_primitive_type((yyvsp[-2].xval)->sym->type) != VAR_S) {
					yyerror("error: functions cannot be used as lvalue");
				}
                (yyval.xval) = make_assign((yyvsp[-2].xval), (yyvsp[0].xval));        
              }
#line 1784 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 208 "parser.y" /* yacc.c:1646  */
    {
			(yyval.xval) = make_iftableitem((yyvsp[0].xval));
		  }
#line 1792 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 213 "parser.y" /* yacc.c:1646  */
    {
			(yyval.xval) = newexpr(programfunc_e);
			(yyval.xval)->sym = (yyvsp[-1].eval);
		  }
#line 1801 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 217 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval); 
          }
#line 1809 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 222 "parser.y" /* yacc.c:1646  */
    {
            /* lookup, starting from the currently active scope, ending at the global scope */
            SymbolTableEntry *entry = lookup((yyvsp[0].sval));               
            if(entry) {
                if(!is_accessible(entry)) yyerror("error: symbol is not accessible");
            }else {
                if(active_scope == 0) entry = insert((yyvsp[0].sval), active_scope, yylineno, GLOBALVAR, NULL, -1);
                else entry = insert((yyvsp[0].sval), active_scope, yylineno, VARVAR, NULL, -1);
            }
            (yyval.xval) = make_lvalue_expr(entry);
          }
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 233 "parser.y" /* yacc.c:1646  */
    {
            /* lookup on the currently active scope */
            SymbolTableEntry *entry = lookup_on_scope((yyvsp[0].sval), active_scope);
            if(active_scope != 0 && is_lib_func((yyvsp[0].sval))) {
                yyerror("error: library functions cannot be shadowed");
                entry = lookup_on_scope((yyvsp[0].sval), 0);
            }else if(!entry) {
                if(active_scope == 0) entry = insert((yyvsp[0].sval), active_scope, yylineno, GLOBALVAR, NULL, -1);
                else entry = insert((yyvsp[0].sval), active_scope, yylineno, LOCALVAR, NULL, -1);
            }
            (yyval.xval) = make_lvalue_expr(entry);  
          }
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 245 "parser.y" /* yacc.c:1646  */
    {
            /* lookup on the global scope */
            SymbolTableEntry *entry = lookup_on_scope((yyvsp[0].sval), 0);
            if(!entry) {
                yyerror("error: symbol not found");
				entry = new_empty_entry();
				entry->name = "_missingno";
            }
            (yyval.xval) = make_lvalue_expr(entry);
          }
#line 1857 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 258 "parser.y" /* yacc.c:1646  */
    { 
                (yyval.xval) = make_member_item((yyvsp[-2].xval), (yyvsp[0].sval)); 
              }
#line 1865 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 261 "parser.y" /* yacc.c:1646  */
    {
                (yyvsp[-3].xval) = make_iftableitem((yyvsp[-3].xval));
                (yyval.xval) = newexpr(tableitem_e);
                (yyval.xval)->sym = (yyvsp[-3].xval)->sym;
                (yyval.xval)->index = (yyvsp[-1].xval);
              }
#line 1876 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 274 "parser.y" /* yacc.c:1646  */
    {
		    (yyval.xval) = make_call((yyvsp[-3].xval), (yyvsp[-1].xval));
		  }
#line 1884 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 277 "parser.y" /* yacc.c:1646  */
    {
			if((yyvsp[0].cval)->method) {
				Expr *self = (yyvsp[-1].xval);
				(yyvsp[-1].xval) = make_iftableitem(make_member_item(self, (yyvsp[0].cval)->name));
				Expr *tmp = (yyvsp[0].cval)->elist;
				if(tmp != NULL) {
					while(tmp->next != NULL) tmp = tmp->next;
				}
				tmp->next = self;
		  	}
			(yyval.xval) = make_call((yyvsp[-1].xval), (yyvsp[0].cval)->elist);
		  }
#line 1901 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 289 "parser.y" /* yacc.c:1646  */
    { 
			Expr *func = newexpr(programfunc_e);
			func->sym = (yyvsp[-4].eval);
			(yyval.xval) = make_call(func, (yyvsp[-1].xval));
		  }
#line 1911 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 296 "parser.y" /* yacc.c:1646  */
    {
                (yyval.cval) = (yyvsp[0].cval);
              }
#line 1919 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 299 "parser.y" /* yacc.c:1646  */
    {
                (yyval.cval) = (yyvsp[0].cval);
              }
#line 1927 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 304 "parser.y" /* yacc.c:1646  */
    {
                (yyval.cval) = malloc(sizeof(CallsuffixObj));
                (yyval.cval)->elist = (yyvsp[-1].xval);
                (yyval.cval)->method = 0;
                (yyval.cval)->name = NULL;
              }
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 312 "parser.y" /* yacc.c:1646  */
    {
                (yyval.cval) = malloc(sizeof(CallsuffixObj));
                (yyval.cval)->elist = (yyvsp[-1].xval);
                (yyval.cval)->method = 1;
                (yyval.cval)->name = (yyvsp[-3].sval);
			  }
#line 1949 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 320 "parser.y" /* yacc.c:1646  */
    {
                (yyval.xval) = make_table((yyvsp[-1].xval), 0);
              }
#line 1957 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 323 "parser.y" /* yacc.c:1646  */
    {
                (yyval.xval) = make_table((yyvsp[-1].xval), 1);
              }
#line 1965 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 331 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval);
          }
#line 1973 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 334 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = NULL;
          }
#line 1981 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 339 "parser.y" /* yacc.c:1646  */
    {
                (yyval.xval) = (yyvsp[0].xval);
              }
#line 1989 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 342 "parser.y" /* yacc.c:1646  */
    {
                (yyval.xval) = (yyvsp[0].xval);
                (yyval.xval)->next =  (yyvsp[-2].xval);
				(yyvsp[-2].xval)->prev = (yyval.xval);
              }
#line 1999 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 349 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval);
          }
#line 2007 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 352 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = (yyvsp[0].xval);
            (yyval.xval)->next = (yyvsp[-2].xval);
			(yyvsp[-2].xval)->prev = (yyval.xval);
          }
#line 2017 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 359 "parser.y" /* yacc.c:1646  */
    { 
                (yyval.xval) = (yyvsp[-3].xval);
                (yyval.xval)->index = (yyvsp[-1].xval);
              }
#line 2026 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 365 "parser.y" /* yacc.c:1646  */
    {
              if(!funcflag) {
                  if(++active_scope > scope_depth) scope_depth++;
              }else{
                  funcflag = 0;
              } 
          }
#line 2038 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 373 "parser.y" /* yacc.c:1646  */
    {
              hide(active_scope--);  
          }
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 378 "parser.y" /* yacc.c:1646  */
    {
					new_stop(&return_list);
					infunc_counter++;
                    push_loopcounter(); 
                    loopcounter = 0;
                  }
#line 2057 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 386 "parser.y" /* yacc.c:1646  */
    {
					infunc_counter--;
                    loopcounter = pop_loopcounter(); 
                  }
#line 2066 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 393 "parser.y" /* yacc.c:1646  */
    {
                (yyval.sval) = (yyvsp[0].sval);
              }
#line 2074 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 396 "parser.y" /* yacc.c:1646  */
    {
                (yyval.sval) = get_funcname();
              }
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 401 "parser.y" /* yacc.c:1646  */
    {
                if(is_unnamed_funcname((yyvsp[-1].sval))) {
                    (yyval.eval) = insert((yyvsp[-1].sval), active_scope, yylineno, USERFUNC, NULL, -1);
                    func_entry = (yyval.eval);
                }else {
                    /* lookup on the currently active scope */
                    (yyval.eval) = lookup_on_scope((yyvsp[-1].sval), active_scope);
                    if(is_lib_func((yyvsp[-1].sval))) {
                        yyerror("error: library functions cannot be shadowed");
                    }else if((yyval.eval)) {
                        yyerror("error: symbol already defined");
                    }else{
                        (yyval.eval) = insert((yyvsp[-1].sval), active_scope, yylineno, USERFUNC, NULL, -1);
                        func_entry = (yyval.eval);	
                    }
                }
                (yyval.eval)->address = currQuad;
                emit(funcstart, NULL, NULL, make_lvalue_expr((yyval.eval)), 0);
            	push_offset();
                scopeSpaceCounter++;
                formalArgOffset = 0;
              }
#line 2109 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 425 "parser.y" /* yacc.c:1646  */
    {
                funcflag = 1;
                if(++active_scope > scope_depth) scope_depth++;	
              }
#line 2118 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 429 "parser.y" /* yacc.c:1646  */
    {
                if(func_entry) {
                    func_entry->argc = funcargc;
                    func_entry->args = funcargs;
                    reset_funcargs();
                }
              }
#line 2130 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 436 "parser.y" /* yacc.c:1646  */
    {
                scopeSpaceCounter++;
                functionLocalOffset = 0;
              }
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 442 "parser.y" /* yacc.c:1646  */
    {
                scopeSpaceCounter--;
              }
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 447 "parser.y" /* yacc.c:1646  */
    {
            scopeSpaceCounter--;
            (yyvsp[-2].eval)->totallocals = functionLocalOffset;
            functionLocalOffset = pop_offset();
            (yyval.eval) = (yyvsp[-2].eval);
            emit(funcend, NULL, NULL, make_lvalue_expr((yyvsp[-2].eval)), 0);
			set_stop_labels(&return_list, currQuad-1);
          }
#line 2160 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 457 "parser.y" /* yacc.c:1646  */
    {   
            (yyval.xval) = newexpr_constnum((yyvsp[0].ival));
          }
#line 2168 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 460 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = newexpr_constnum((yyvsp[0].rval));
          }
#line 2176 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 463 "parser.y" /* yacc.c:1646  */
    {      
            (yyval.xval) = newexpr_conststring((yyvsp[0].sval));
          }
#line 2184 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 466 "parser.y" /* yacc.c:1646  */
    {              
            (yyval.xval) = newexpr(nil_e);
          }
#line 2192 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 469 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = newexpr_constbool(1);
          }
#line 2200 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 472 "parser.y" /* yacc.c:1646  */
    {
            (yyval.xval) = newexpr_constbool(0);
          }
#line 2208 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 481 "parser.y" /* yacc.c:1646  */
    {
                /* lookup on the currently active scope */
                if(is_lib_func((yyvsp[0].sval))) {
                    yyerror("error: library functions cannot be shadowed");
                }else {
                    insert((yyvsp[0].sval), active_scope, yylineno, FORMALVAR, NULL, -1);
                    if(func_entry) {
                        if(funcargc == max_funcargc) grow_funcargs();
                        funcargs[funcargc++] = strdup((yyvsp[0].sval));
                    }
                }
              }
#line 2225 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 493 "parser.y" /* yacc.c:1646  */
    {  
                /* lookup on the currently active scope */
                SymbolTableEntry *entry = lookup_on_scope((yyvsp[0].sval), active_scope);
                if(is_lib_func((yyvsp[0].sval))) {
                    yyerror("error: library functions cannot be shadowed");
                }else if(entry) {
                    yyerror("error: symbol already defined");
                }else {
                    insert((yyvsp[0].sval), active_scope, yylineno, FORMALVAR, NULL, -1);
                    if(func_entry) {
                        if(funcargc == max_funcargc) grow_funcargs();
                        funcargs[funcargc++] = strdup((yyvsp[0].sval));
                    }
                }
              }
#line 2245 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 511 "parser.y" /* yacc.c:1646  */
    {
              	emit(if_eq, (yyvsp[-1].xval), newexpr_constbool(1), NULL, currQuad + 2);
				(yyval.ival) = currQuad;
				emit(jump, NULL, NULL, NULL, 0);
        	  }
#line 2255 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 518 "parser.y" /* yacc.c:1646  */
    {
				(yyval.ival) = currQuad;
                emit(jump, NULL, NULL, NULL, 0);
              }
#line 2264 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 524 "parser.y" /* yacc.c:1646  */
    {
			patchlabel((yyvsp[-3].ival), (yyvsp[-1].ival) + 1);
			patchlabel((yyvsp[-1].ival), currQuad);       
          }
#line 2273 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 528 "parser.y" /* yacc.c:1646  */
    {
			patchlabel((yyvsp[-1].ival), currQuad);
          }
#line 2281 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 533 "parser.y" /* yacc.c:1646  */
    {
				new_stop(&break_list);
				new_stop(&continue_list);
				loopcounter++;
			  }
#line 2291 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 540 "parser.y" /* yacc.c:1646  */
    {
				loopcounter--;
			  }
#line 2299 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 548 "parser.y" /* yacc.c:1646  */
    {
				(yyval.ival) = currQuad;
            }
#line 2307 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 553 "parser.y" /* yacc.c:1646  */
    {
                emit(if_eq, (yyvsp[-1].xval), newexpr_constbool(1), NULL, currQuad + 2);
				(yyval.ival) = currQuad;
                emit(jump, NULL, NULL, NULL, 0);
              }
#line 2317 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 560 "parser.y" /* yacc.c:1646  */
    {
                emit(jump, NULL, NULL, NULL, (yyvsp[-2].ival));
                patchlabel((yyvsp[-1].ival), currQuad);
				set_stop_labels(&break_list, currQuad);
				set_stop_labels(&continue_list, (yyvsp[-2].ival));
              }
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 568 "parser.y" /* yacc.c:1646  */
    {
        (yyval.ival) = currQuad; 
        emit(jump, NULL, NULL, NULL, 0); 
      }
#line 2337 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 574 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ival) = currQuad; 
	  }
#line 2345 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 579 "parser.y" /* yacc.c:1646  */
    {
				(yyval.fval) = malloc(sizeof(ForprefixObj));
				(yyval.fval)->test = (yyvsp[-2].ival);
				(yyval.fval)->enter = currQuad;
				emit(if_eq, (yyvsp[-1].xval), newexpr_constbool(1), NULL, 0);
		      }
#line 2356 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 587 "parser.y" /* yacc.c:1646  */
    {
			patchlabel((yyvsp[-6].fval)->enter, (yyvsp[-2].ival) + 1);
			patchlabel((yyvsp[-5].ival), currQuad);
			patchlabel((yyvsp[-2].ival), (yyvsp[-6].fval)->test);
			patchlabel((yyvsp[0].ival), (yyvsp[-5].ival) + 1);
			set_stop_labels(&break_list, currQuad);
			set_stop_labels(&continue_list, (yyvsp[-5].ival) + 1);
          }
#line 2369 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 597 "parser.y" /* yacc.c:1646  */
    {
				if(infunc_counter <= 0)  yyerror("error: return out of function block");
                emit(ret, NULL, NULL, (yyvsp[-1].xval), 0);
              }
#line 2378 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 601 "parser.y" /* yacc.c:1646  */
    {
				if(infunc_counter <= 0)  yyerror("error: return out of function block");
            	emit(ret, NULL, NULL, NULL, 0);
              }
#line 2387 "parser.c" /* yacc.c:1646  */
    break;


#line 2391 "parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 608 "parser.y" /* yacc.c:1906  */


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
