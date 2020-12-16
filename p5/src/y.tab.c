/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "alfa/alfa.y"


/* C delimiters */

  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include "alfa.h"
  #include "symbolsTable.h"
  #include "generator.h"

  #ifdef _DEBUG_
  #define PRINT_RULE(str, val) \
              fprintf(stdout, ";R%d:\t%s\n", val, str);
  #else
  #define PRINT_RULE(str, val)
  #endif

  #define EXITFAIL(str, ...) \
              COPYERR(" "str " ", ##__VA_ARGS__); \
              return PARSEFAIL;
  
  #define PARSEFAIL INT_MAX

  extern char errbuff[BUFF];

  /* Function to extract tokens from morfologic */
  extern int yylex(SymbolsTable *st);

  /* Default input file */
  extern FILE* yyin;

  /* Default yyoutput file */
  extern FILE* yyout;

  /* Default assembly file */
  FPASM;

  /* Common morfoligic error flag defined in "alfa.h" */
  bool morfofailure;

  /* Function launched in case of failure */
  int yyerror(SymbolsTable *st, char *s);

  void write_symbols_table(FPASM, SymbolsTable *st);

  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
  /* - - - - - - GLOBAL VARS - - - - - - - */
  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */

  Symbol *_sgeneric;
  Symbol *_sleft;
  Symbol *_sright;
  Symbol *_smid;

  char __buff[MAX_LEN + 1];

  ElementCategory current_category; /* VAR, PARAM, FUNCT */
  DataType current_type; /* INT, BOOLEAN */
  IdentifierCategory current_class; /* SCALAR, VECTOR */
  Scope current_scope; /* GLOBAL, LOCAL */
  int32_t current_var_pos; /* Position inside funct localvars */
  int32_t current_param_pos; /* Position inside funct params */
  int8_t current_size; /* Vector's size */
  int32_t current_params; /* Function params amount */
  int32_t current_localvars; /* Function localvars amount */
  uint32_t tags = 0; /* Current tags amount */

  bool in_declare; /* true if we're in declarations part, false if not */
  bool in_main; /* true if we're in main part, else false */
  

#line 143 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TOK_MAIN = 258,
    TOK_INT = 259,
    TOK_BOOLEAN = 260,
    TOK_ARRAY = 261,
    TOK_FUNCTION = 262,
    TOK_IF = 263,
    TOK_ELSE = 264,
    TOK_WHILE = 265,
    TOK_SCANF = 266,
    TOK_PRINTF = 267,
    TOK_RETURN = 268,
    TOK_PUNTOYCOMA = 269,
    TOK_COMA = 270,
    TOK_PARENTESISIZQUIERDO = 271,
    TOK_PARENTESISDERECHO = 272,
    TOK_CORCHETEIZQUIERDO = 273,
    TOK_CORCHETEDERECHO = 274,
    TOK_LLAVEIZQUIERDA = 275,
    TOK_LLAVEDERECHA = 276,
    TOK_ASIGNACION = 277,
    TOK_MAS = 278,
    TOK_MENOS = 279,
    TOK_ASTERISCO = 280,
    TOK_DIVISION = 281,
    TOK_MENOR = 282,
    TOK_MAYOR = 283,
    TOK_AND = 284,
    TOK_OR = 285,
    TOK_NOT = 286,
    TOK_IGUAL = 287,
    TOK_DISTINTO = 288,
    TOK_MENORIGUAL = 289,
    TOK_MAYORIGUAL = 290,
    TOK_TRUE = 291,
    TOK_FALSE = 292,
    TOK_ERROR = 293,
    MENOSU = 294,
    TOK_CONSTANTE_ENTERA = 295,
    TOK_IDENTIFICADOR = 296
  };
#endif
/* Tokens.  */
#define TOK_MAIN 258
#define TOK_INT 259
#define TOK_BOOLEAN 260
#define TOK_ARRAY 261
#define TOK_FUNCTION 262
#define TOK_IF 263
#define TOK_ELSE 264
#define TOK_WHILE 265
#define TOK_SCANF 266
#define TOK_PRINTF 267
#define TOK_RETURN 268
#define TOK_PUNTOYCOMA 269
#define TOK_COMA 270
#define TOK_PARENTESISIZQUIERDO 271
#define TOK_PARENTESISDERECHO 272
#define TOK_CORCHETEIZQUIERDO 273
#define TOK_CORCHETEDERECHO 274
#define TOK_LLAVEIZQUIERDA 275
#define TOK_LLAVEDERECHA 276
#define TOK_ASIGNACION 277
#define TOK_MAS 278
#define TOK_MENOS 279
#define TOK_ASTERISCO 280
#define TOK_DIVISION 281
#define TOK_MENOR 282
#define TOK_MAYOR 283
#define TOK_AND 284
#define TOK_OR 285
#define TOK_NOT 286
#define TOK_IGUAL 287
#define TOK_DISTINTO 288
#define TOK_MENORIGUAL 289
#define TOK_MAYORIGUAL 290
#define TOK_TRUE 291
#define TOK_FALSE 292
#define TOK_ERROR 293
#define MENOSU 294
#define TOK_CONSTANTE_ENTERA 295
#define TOK_IDENTIFICADOR 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 77 "alfa/alfa.y"

  attrs_type attrs;

#line 281 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (SymbolsTable *st);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   158,   158,   169,   182,   190,   199,   208,   217,   227,
     237,   246,   255,   265,   281,   293,   302,   312,   320,   354,
     377,   400,   410,   418,   428,   436,   447,   457,   465,   474,
     483,   492,   501,   510,   519,   528,   537,   546,   556,   582,
     591,   600,   611,   619,   626,   640,   649,   673,   685,   694,
     711,   726,   740,   749,   766,   775,   784,   794,   820,   831,
     840,   851,   860,   869,   879,   887,   897,   905,   922,   938,
     955,   972,   989,  1006,  1015,  1026,  1035,  1044,  1059
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_MAIN", "TOK_INT", "TOK_BOOLEAN",
  "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_PUNTOYCOMA", "TOK_COMA",
  "TOK_PARENTESISIZQUIERDO", "TOK_PARENTESISDERECHO",
  "TOK_CORCHETEIZQUIERDO", "TOK_CORCHETEDERECHO", "TOK_LLAVEIZQUIERDA",
  "TOK_LLAVEDERECHA", "TOK_ASIGNACION", "TOK_MAS", "TOK_MENOS",
  "TOK_ASTERISCO", "TOK_DIVISION", "TOK_MENOR", "TOK_MAYOR", "TOK_AND",
  "TOK_OR", "TOK_NOT", "TOK_IGUAL", "TOK_DISTINTO", "TOK_MENORIGUAL",
  "TOK_MAYORIGUAL", "TOK_TRUE", "TOK_FALSE", "TOK_ERROR", "MENOSU",
  "TOK_CONSTANTE_ENTERA", "TOK_IDENTIFICADOR", "$accept", "program", "er1",
  "er2", "declarations", "declaration", "class", "class_scalar", "type",
  "class_vector", "identifiers", "functions", "function", "fn_name",
  "fn_declarations", "function_params", "remaining_function_params",
  "function_param", "function_declarations", "statements", "statement",
  "simple_statement", "block", "assignment", "vector_element",
  "conditional", "if_exp_stm", "if_exp", "loop", "reading", "writing",
  "function_return", "exp", "exp_list", "exp_remaining_list", "comparison",
  "constant", "constant_logic", "constant_int", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,    -5,    28,    33,   -32,   -32,   -32,    21,   -32,    33,
     -10,   -32,   -32,   -32,    22,    34,   -32,   -32,    29,    38,
      18,    21,   -32,    34,    43,     9,   -32,   -10,   -32,    56,
      37,     9,   -32,    21,    46,    70,    49,    11,    11,    -9,
      66,     9,    77,   -32,   -32,    76,   -32,    83,     9,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,    72,    63,    88,    92,
      11,    11,   -32,    11,    11,    11,   -32,   -32,    -4,   -32,
      47,   -32,   -32,   -32,    47,    11,    11,   -32,   -32,   -32,
      11,   102,   107,   -32,   -32,   115,    21,   -32,    71,   100,
      86,   119,   -32,   -32,    11,    11,    11,    11,    11,    11,
      11,   108,    47,    47,     9,   -32,    33,    92,   120,   121,
     -32,    11,    11,    11,    11,    11,    11,   -32,    31,   122,
     -21,   -21,   -32,   -32,   -32,   -21,   -32,   123,   -32,   -32,
     -32,   -32,     9,    47,    47,    47,    47,    47,    47,    11,
     -32,   -32,   -32,   124,    31,   -32,   -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    11,    12,     0,     3,     5,
       0,     8,    10,     9,     0,    17,     6,    78,     0,    14,
       0,     0,     4,    17,     0,     0,     7,     0,    77,     0,
       0,     0,    16,    22,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    31,    32,     0,    36,    41,     0,    37,
      33,    34,    35,    15,    13,    19,     0,     0,     0,    24,
       0,     0,    46,     0,     0,     0,    75,    76,    57,    61,
      47,    58,    73,    74,    48,     0,     0,    18,    29,    30,
       0,     0,     0,     2,    25,     0,     0,    21,     0,     0,
       0,     0,    53,    56,    64,     0,     0,     0,     0,     0,
       0,     0,    38,    39,     0,    43,    27,    24,     0,     0,
      59,     0,     0,     0,     0,     0,     0,    60,    66,     0,
      49,    50,    52,    51,    54,    55,    40,     0,    26,    20,
      23,    44,     0,    71,    72,    67,    68,    69,    70,     0,
      63,    62,    42,     0,    66,    45,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   -32,    -7,   -32,   -32,   -32,     3,   -32,
     116,   125,   -32,   -32,   -32,   -32,    35,    60,   -32,   -30,
     -32,   -32,   -32,   -32,   -25,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -31,   -32,     5,   -32,   -32,   -32,   127,   -32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    15,    31,     8,     9,    10,    11,    12,    13,
      18,    22,    23,    24,    25,    58,    87,    59,   129,    40,
      41,    42,    43,    44,    69,    46,    47,    48,    49,    50,
      51,    52,    70,   119,   140,    91,    71,    72,    73,    19
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    56,    16,     1,    97,    98,    45,    74,    99,    75,
      14,    78,    94,    76,    75,     3,    45,    34,    82,    35,
      36,    37,    38,    45,    30,     5,     6,    63,     4,    88,
      89,    17,    90,    92,    93,    64,    57,     5,     6,     7,
      20,    21,    65,    26,   101,   102,   139,    66,    67,   103,
      39,    28,    68,    27,    95,    96,    97,    98,    28,    33,
      99,   100,    60,   118,   120,   121,   122,   123,   124,   125,
      95,    96,    97,    98,   127,    54,    99,   100,    55,    45,
     133,   134,   135,   136,   137,   138,    61,    77,   108,    57,
      62,    79,    81,    83,    95,    96,    97,    98,    80,   128,
      99,   100,   143,   110,    84,    85,    86,    45,   144,    95,
      96,    97,    98,   111,   112,    99,   100,   109,   113,   114,
     115,   116,   104,    95,    96,    97,    98,   126,   105,    99,
     100,    95,    96,    97,    98,   106,   117,    99,   100,   141,
     131,   132,   130,    53,   142,   145,   107,    29,    32,   146
};

static const yytype_uint8 yycheck[] =
{
      25,    31,     9,     3,    25,    26,    31,    38,    29,    18,
       7,    41,    16,    22,    18,    20,    41,     8,    48,    10,
      11,    12,    13,    48,    21,     4,     5,    16,     0,    60,
      61,    41,    63,    64,    65,    24,    33,     4,     5,     6,
      18,     7,    31,    14,    75,    76,    15,    36,    37,    80,
      41,    40,    41,    15,    23,    24,    25,    26,    40,    16,
      29,    30,    16,    94,    95,    96,    97,    98,    99,   100,
      23,    24,    25,    26,   104,    19,    29,    30,    41,   104,
     111,   112,   113,   114,   115,   116,    16,    21,    17,    86,
      41,    14,     9,    21,    23,    24,    25,    26,    22,   106,
      29,    30,   132,    17,    41,    17,    14,   132,   139,    23,
      24,    25,    26,    27,    28,    29,    30,    17,    32,    33,
      34,    35,    20,    23,    24,    25,    26,    19,    21,    29,
      30,    23,    24,    25,    26,    20,    17,    29,    30,    17,
      20,    20,   107,    27,    21,    21,    86,    20,    23,   144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    43,    20,     0,     4,     5,     6,    46,    47,
      48,    49,    50,    51,    50,    44,    46,    41,    52,    81,
      18,     7,    53,    54,    55,    56,    14,    15,    40,    80,
      50,    45,    53,    16,     8,    10,    11,    12,    13,    41,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    52,    19,    41,    61,    50,    57,    59,
      16,    16,    41,    16,    24,    31,    36,    37,    41,    66,
      74,    78,    79,    80,    74,    18,    22,    21,    61,    14,
      22,     9,    61,    21,    41,    17,    14,    58,    74,    74,
      74,    77,    74,    74,    16,    23,    24,    25,    26,    29,
      30,    74,    74,    74,    20,    21,    20,    59,    17,    17,
      17,    27,    28,    32,    33,    34,    35,    17,    74,    75,
      74,    74,    74,    74,    74,    74,    19,    61,    46,    60,
      58,    20,    20,    74,    74,    74,    74,    74,    74,    15,
      76,    17,    21,    61,    74,    21,    76
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    45,    46,    46,    47,    48,    48,
      49,    50,    50,    51,    52,    52,    53,    53,    54,    55,
      56,    57,    57,    58,    58,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    69,    70,    71,    72,    73,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    78,    78,    79,    79,    80,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     0,     0,     1,     2,     3,     1,     1,
       1,     1,     1,     5,     1,     3,     2,     0,     3,     3,
       6,     2,     0,     3,     0,     2,     1,     0,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       4,     1,     5,     3,     5,     7,     2,     2,     2,     3,
       3,     3,     3,     2,     3,     3,     2,     1,     1,     3,
       3,     1,     4,     2,     0,     3,     0,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (st, YY_("syntax error: cannot back up")); \
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
                  Type, Value, st); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, SymbolsTable *st)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (st);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, SymbolsTable *st)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, st);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, SymbolsTable *st)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , st);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, st); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, SymbolsTable *st)
{
  YYUSE (yyvaluep);
  YYUSE (st);
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
yyparse (SymbolsTable *st)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex (st);
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2:
#line 159 "alfa/alfa.y"
      {
        PRINT_RULE("<programa> ::= main { <declaraciones> <funciones> <sentencias> }", 1);
        write_end(FPASM_NAME);
      }
#line 1569 "y.tab.c"
    break;

  case 3:
#line 169 "alfa/alfa.y"
    {
      write_data_header(FPASM_NAME);
      write_bss_header(FPASM_NAME);
      write_symbols_table(FPASM_NAME, st);
      write_code_segment(FPASM_NAME);
      in_declare = false;
    }
#line 1581 "y.tab.c"
    break;

  case 4:
#line 182 "alfa/alfa.y"
    {
      write_main_begin(FPASM_NAME);
    }
#line 1589 "y.tab.c"
    break;

  case 5:
#line 191 "alfa/alfa.y"
            {
              PRINT_RULE("<declaraciones> ::= <declaracion>", 2);
            }
#line 1597 "y.tab.c"
    break;

  case 6:
#line 200 "alfa/alfa.y"
            {
              PRINT_RULE("<declaraciones> ::= <declaracion> <declaraciones>", 3);
            }
#line 1605 "y.tab.c"
    break;

  case 7:
#line 209 "alfa/alfa.y"
          {
            PRINT_RULE("<declaracion> ::= <clase> <identificadores> ;", 4);
          }
#line 1613 "y.tab.c"
    break;

  case 8:
#line 218 "alfa/alfa.y"
      {
        PRINT_RULE("<clase> ::= <clase_escalar>", 5);
        current_class = SCALAR;
      }
#line 1622 "y.tab.c"
    break;

  case 9:
#line 228 "alfa/alfa.y"
      {
        PRINT_RULE("<clase> ::= <clase_vector>", 7);
        current_class = VECTOR;
      }
#line 1631 "y.tab.c"
    break;

  case 10:
#line 238 "alfa/alfa.y"
            {
              PRINT_RULE("<clase_escalar> ::= <tipo> ", 9);
            }
#line 1639 "y.tab.c"
    break;

  case 11:
#line 247 "alfa/alfa.y"
      {
        PRINT_RULE("<tipo> ::= int", 10);
        current_type = INT;
      }
#line 1648 "y.tab.c"
    break;

  case 12:
#line 256 "alfa/alfa.y"
      {
        PRINT_RULE("<tipo> ::= boolean", 11);
        current_type = BOOLEAN;
      }
#line 1657 "y.tab.c"
    break;

  case 13:
#line 266 "alfa/alfa.y"
            {
              PRINT_RULE("<clase_vector> ::= array <tipo> [ <constante_entera> ]", 15);
              
              current_size = (yyvsp[-1].attrs).int_value;
              if( current_size < _VECTOR_MIN_LEN_ ||
                    current_size > _VECTOR_MAX_LEN_ )
              {
                EXITFAIL("Vector's size out of allowed bounds");
              }
            }
#line 1672 "y.tab.c"
    break;

  case 14:
#line 282 "alfa/alfa.y"
          {
            PRINT_RULE("<identificadores> ::= <identificador>", 18);

            
          }
#line 1682 "y.tab.c"
    break;

  case 15:
#line 294 "alfa/alfa.y"
          {
            PRINT_RULE("<identificadores> ::= <identificador> , <identificadores>", 19);
          }
#line 1690 "y.tab.c"
    break;

  case 16:
#line 303 "alfa/alfa.y"
        {
          PRINT_RULE("<funciones> :: <funcion> <funciones>", 20);
        }
#line 1698 "y.tab.c"
    break;

  case 17:
#line 312 "alfa/alfa.y"
        {
          PRINT_RULE("<funciones> ::= ", 21);
        }
#line 1706 "y.tab.c"
    break;

  case 18:
#line 321 "alfa/alfa.y"
        {
          PRINT_RULE("<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }", 22);

          if(( _sgeneric = st_searchCurrentScope(st, (yyvsp[-2].attrs).lexeme)) == NULL )
          {
            EXITFAIL("Fatal error. Function identifier %s not found! ", (yyvsp[-2].attrs).lexeme);
          }

          if ( !stopLocalScope(st) )
          {
            EXITFAIL("Fatal error, %s's scope coulnd't be closed.", (yyvsp[-2].attrs).lexeme);
          }

          if (( _sgeneric = st_searchCurrentScope(st, (yyvsp[-2].attrs).lexeme)) == NULL)
          {
            EXITFAIL("Fatal error. Function identifier %s not in global scope", (yyvsp[-2].attrs).lexeme );
          }

          symbol_configure_function(
            _sgeneric,
            current_params,
            current_localvars,
            (yyvsp[-2].attrs).type
          );

          (yyval.attrs).type = (yyvsp[-2].attrs).type; // propagate function return type
                strcpy((yyval.attrs).lexeme, (yyvsp[-2].attrs).lexeme); // propagate function name
        }
#line 1739 "y.tab.c"
    break;

  case 19:
#line 355 "alfa/alfa.y"
      {
        if(( _sgeneric = st_searchCurrentScope(st, (yyvsp[0].attrs).lexeme)) != NULL )
        {
          EXITFAIL("Identifier %s already exist. ", (yyvsp[0].attrs).lexeme);
        }
        if ( !declareFunction( st, (yyvsp[0].attrs).lexeme, (yyvsp[-1].attrs).type, (yyvsp[0].attrs).int_value) )
        {
          EXITFAIL("Function %s could't be declared. ", (yyvsp[0].attrs).lexeme );
        }
        current_localvars = 0;
        current_var_pos = 1;
        current_params = 0;
        current_param_pos = 0;

        (yyval.attrs).type = (yyvsp[-1].attrs).type; // propagate function return type
        strcpy((yyval.attrs).lexeme, (yyvsp[0].attrs).lexeme); // propagate function name
      }
#line 1761 "y.tab.c"
    break;

  case 20:
#line 379 "alfa/alfa.y"
              {
                if(( _sgeneric = st_searchCurrentScope(st, (yyvsp[-5].attrs).lexeme )) == NULL )
                {
                  EXITFAIL("Fatal error. Function identifier %s not found", (yyvsp[-5].attrs).lexeme);
                }

                symbol_configure_function(
                  _sgeneric,
                  current_params,
                  current_localvars,
                  (yyvsp[-5].attrs).type
                );

                (yyval.attrs).type = (yyvsp[-5].attrs).type; // propagate function return type
                strcpy((yyval.attrs).lexeme, (yyvsp[-5].attrs).lexeme); // propagate function name
              }
#line 1782 "y.tab.c"
    break;

  case 21:
#line 401 "alfa/alfa.y"
              {
                PRINT_RULE("<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>", 23);
              }
#line 1790 "y.tab.c"
    break;

  case 22:
#line 410 "alfa/alfa.y"
              {
                PRINT_RULE("<parametros_funcion> ::= ", 24);
              }
#line 1798 "y.tab.c"
    break;

  case 23:
#line 419 "alfa/alfa.y"
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>", 25);
                        }
#line 1806 "y.tab.c"
    break;

  case 24:
#line 428 "alfa/alfa.y"
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ", 26);
                        }
#line 1814 "y.tab.c"
    break;

  case 25:
#line 437 "alfa/alfa.y"
              {
                PRINT_RULE("<parametro_funcion> ::= <tipo> <identificador>", 27);


              }
#line 1824 "y.tab.c"
    break;

  case 26:
#line 448 "alfa/alfa.y"
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= <declaraciones>", 28);
                    }
#line 1832 "y.tab.c"
    break;

  case 27:
#line 457 "alfa/alfa.y"
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= ", 29);
                    }
#line 1840 "y.tab.c"
    break;

  case 28:
#line 466 "alfa/alfa.y"
          {
            PRINT_RULE("<sentencias> ::= <sentencia>", 30);
          }
#line 1848 "y.tab.c"
    break;

  case 29:
#line 475 "alfa/alfa.y"
          {
            PRINT_RULE("<sentencias> ::= <sentencia> <sentencias>", 31);
          }
#line 1856 "y.tab.c"
    break;

  case 30:
#line 484 "alfa/alfa.y"
        {
          PRINT_RULE("<sentencia> ::= <sentencia_simple> ;", 32);
        }
#line 1864 "y.tab.c"
    break;

  case 31:
#line 493 "alfa/alfa.y"
        {
          PRINT_RULE("<sentencia> ::= <bloque>", 33);
        }
#line 1872 "y.tab.c"
    break;

  case 32:
#line 502 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <asignacion>", 34);
              }
#line 1880 "y.tab.c"
    break;

  case 33:
#line 511 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <lectura>", 35);
              }
#line 1888 "y.tab.c"
    break;

  case 34:
#line 520 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <escritura>", 36);
              }
#line 1896 "y.tab.c"
    break;

  case 35:
#line 529 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <retorno_funcion>", 38);
              }
#line 1904 "y.tab.c"
    break;

  case 36:
#line 538 "alfa/alfa.y"
    {
      PRINT_RULE("<bloque> ::= <condicional>", 40);
    }
#line 1912 "y.tab.c"
    break;

  case 37:
#line 547 "alfa/alfa.y"
    {
      PRINT_RULE("<bloque> ::= <bubcle>", 41);
    }
#line 1920 "y.tab.c"
    break;

  case 38:
#line 557 "alfa/alfa.y"
    {
      PRINT_RULE("<asignacion> ::= <identificador> = <exp>", 43);
      if((_sleft = st_searchCurrentScope(st, (yyvsp[-2].attrs).lexeme)) == NULL)
        /* Symbol is not declared */
        EXITFAIL("Identifier %s not declared.", (yyvsp[-2].attrs).lexeme);
      if(symbol_get_category(_sleft) == FUNCT)
      {
        EXITFAIL("Identifier %s is a function.", (yyvsp[-2].attrs).lexeme);
      }
      else if(symbol_blind_identifierCategory(_sleft) == VECTOR)
      {
        EXITFAIL("Identifier %s is a vector.", (yyvsp[-2].attrs).lexeme);
      }  
      else if(symbol_blind_dataType(_sleft) != (yyvsp[0].attrs).type)
      {
        EXITFAIL("Identifiers type missmatch")
      }

      write_assignment(FPASM_NAME, (yyvsp[-2].attrs).lexeme, (yyvsp[0].attrs).is_var);
    }
#line 1945 "y.tab.c"
    break;

  case 39:
#line 583 "alfa/alfa.y"
    {
      PRINT_RULE("<asignacion> ::= <elemento_vector> = <exp>", 44);
    }
#line 1953 "y.tab.c"
    break;

  case 40:
#line 592 "alfa/alfa.y"
              {
                PRINT_RULE("<elemento_vector> ::= <identificador> [ <exp> ]", 48);
              }
#line 1961 "y.tab.c"
    break;

  case 41:
#line 601 "alfa/alfa.y"
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", 50);
            (yyval.attrs).tags = (yyvsp[0].attrs).tags;
            write_ifthenelse_end(FPASM_NAME, (yyval.attrs).tags);
          }
#line 1971 "y.tab.c"
    break;

  case 42:
#line 612 "alfa/alfa.y"
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", 51);
            (yyval.attrs).tags = (yyvsp[-4].attrs).tags;
            write_ifthenelse_end(FPASM_NAME, (yyval.attrs).tags);
          }
#line 1981 "y.tab.c"
    break;

  case 43:
#line 620 "alfa/alfa.y"
          {
            (yyval.attrs).tags = (yyvsp[-2].attrs).tags;
            write_ifthenelse_middle(FPASM_NAME, (yyval.attrs).tags);
          }
#line 1990 "y.tab.c"
    break;

  case 44:
#line 627 "alfa/alfa.y"
      {
        if((yyvsp[-2].attrs).type != BOOLEAN)
        {
          EXITFAIL("Type missmatch. 'IF' requires boolean exp");
        }
        (yyval.attrs).tags = tags++;
        write_ifthenelse_begin(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyval.attrs).tags);
      }
#line 2003 "y.tab.c"
    break;

  case 45:
#line 641 "alfa/alfa.y"
    {
      PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", 52);
    }
#line 2011 "y.tab.c"
    break;

  case 46:
#line 650 "alfa/alfa.y"
      {
        PRINT_RULE("<lectura> ::= scanf <identificador>", 54);

        if((_sgeneric = st_searchCurrentScope(st, (yyvsp[0].attrs).lexeme)) == NULL)
        {
          EXITFAIL("Identifier not found");
        }
        if(symbol_get_category(_sgeneric) == FUNCT)
        {
          EXITFAIL("Trying to print a function");
        }
        else if(symbol_blind_identifierCategory(_sgeneric) == VECTOR)
        {
          EXITFAIL("Trying to print a vector");
        }

        write_reading(FPASM_NAME, (yyvsp[0].attrs).lexeme, (yyvsp[0].attrs).type);
      }
#line 2034 "y.tab.c"
    break;

  case 47:
#line 674 "alfa/alfa.y"
      {
        PRINT_RULE("<escritura> ::= printf <exp>", 56);

        write_writing(FPASM_NAME, (yyvsp[0].attrs).is_var, (yyvsp[0].attrs).type);

      }
#line 2045 "y.tab.c"
    break;

  case 48:
#line 686 "alfa/alfa.y"
      {
        PRINT_RULE("<retorno_funcion> ::= return <exp>", 61);
      }
#line 2053 "y.tab.c"
    break;

  case 49:
#line 695 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> + <exp>", 72);
      if((yyvsp[-2].attrs).type != (yyvsp[0].attrs).type || ((yyvsp[-2].attrs).type != INT && (yyvsp[-2].attrs).type != BOOLEAN))
      {
        EXITFAIL("Types missmatch");
      }

      write_sum(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var);
      (yyval.attrs).type = (yyvsp[-2].attrs).type; // also $$.type = $3.type
      (yyval.attrs).is_var = false;
    }
#line 2069 "y.tab.c"
    break;

  case 50:
#line 712 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> - <exp>", 73);
      if( (yyvsp[-2].attrs).type != (yyvsp[0].attrs).type || ((yyvsp[-2].attrs).type != INT && (yyvsp[-2].attrs).type != BOOLEAN) )
      {
        EXITFAIL("Substract requires both values to be the same");
      }

      write_subtract( FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var );
    }
#line 2083 "y.tab.c"
    break;

  case 51:
#line 727 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> / <exp>", 74);
      if( (yyvsp[-2].attrs).type != (yyvsp[0].attrs).type || ((yyvsp[-2].attrs).type != INT) )
      {
        EXITFAIL("Division requires both values to be integers");
      }
      
    }
#line 2096 "y.tab.c"
    break;

  case 52:
#line 741 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> * <exp>", 75);
    }
#line 2104 "y.tab.c"
    break;

  case 53:
#line 750 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= - <exp>", 76);
      if((yyvsp[0].attrs).type != INT)
      {
        EXITFAIL("Types missmatch. - <exp> requires integer value");
      }

      write_sign_change( FPASM_NAME, (yyvsp[0].attrs).is_var );
      (yyval.attrs).is_var = false;
      (yyval.attrs).type = INT;
    }
#line 2120 "y.tab.c"
    break;

  case 54:
#line 767 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> && <exp>", 77);
    }
#line 2128 "y.tab.c"
    break;

  case 55:
#line 776 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> || <exp>", 78);
    }
#line 2136 "y.tab.c"
    break;

  case 56:
#line 785 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ! <exp>", 79);
    }
#line 2144 "y.tab.c"
    break;

  case 57:
#line 795 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <identificador>", 80);
      if((_sleft = st_searchCurrentScope(st, (yyvsp[0].attrs).lexeme)) == NULL)
      {
        EXITFAIL("Identifier %s doesn't exists", (yyvsp[0].attrs).lexeme);
      }
      if(symbol_get_category(_sleft) == FUNCT)
      {
        EXITFAIL("Identifier %s is a function", (yyvsp[0].attrs).lexeme);
      }
      else if(symbol_blind_identifierCategory(_sleft) == VECTOR)
      {
        EXITFAIL("Identifier %s is a vector", (yyvsp[0].attrs).lexeme);
      }

      (yyval.attrs).type = symbol_blind_dataType(_sleft);
      (yyval.attrs).is_var = true;

      write_operand(FPASM_NAME, (yyvsp[0].attrs).lexeme, (yyval.attrs).is_var);
    }
#line 2169 "y.tab.c"
    break;

  case 58:
#line 821 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <constante>", 81);
      (yyval.attrs).type = (yyvsp[0].attrs).type;
      (yyval.attrs).is_var = (yyvsp[0].attrs).is_var;
    }
#line 2179 "y.tab.c"
    break;

  case 59:
#line 832 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ( <exp> )", 82);
    }
#line 2187 "y.tab.c"
    break;

  case 60:
#line 841 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ( <comparacion> )", 83);
      (yyval.attrs).type = (yyvsp[-1].attrs).type;
      (yyval.attrs).is_var = (yyvsp[-1].attrs).is_var;
    }
#line 2197 "y.tab.c"
    break;

  case 61:
#line 852 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <elemento_vector>", 85);
    }
#line 2205 "y.tab.c"
    break;

  case 62:
#line 861 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <identificador> ( <lista_expresiones> )", 88);
    }
#line 2213 "y.tab.c"
    break;

  case 63:
#line 870 "alfa/alfa.y"
        {
          PRINT_RULE("<lista_expresiones> ::= <exp> <resto_lista_expresiones>", 89);
        }
#line 2221 "y.tab.c"
    break;

  case 64:
#line 879 "alfa/alfa.y"
        {
          PRINT_RULE("<lista_expresiones> ::= ", 90);
        }
#line 2229 "y.tab.c"
    break;

  case 65:
#line 888 "alfa/alfa.y"
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>", 91);
                  }
#line 2237 "y.tab.c"
    break;

  case 66:
#line 897 "alfa/alfa.y"
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= ", 92);
                  }
#line 2245 "y.tab.c"
    break;

  case 67:
#line 906 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> == <exp>", 93);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[-2].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required.");
            }
            
            write_equal(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2261 "y.tab.c"
    break;

  case 68:
#line 923 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> != <exp>", 94);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[0].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            write_different(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2276 "y.tab.c"
    break;

  case 69:
#line 939 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> <= <exp>", 95);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[0].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            
            write_lower_equal(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2292 "y.tab.c"
    break;

  case 70:
#line 956 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> >= <exp>", 96);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[0].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }

            write_greater_equal(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2308 "y.tab.c"
    break;

  case 71:
#line 973 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> < <exp>", 97);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[0].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }
            
            write_lower(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2324 "y.tab.c"
    break;

  case 72:
#line 990 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> > <exp>", 98);
            if((yyvsp[-2].attrs).type != INT || (yyvsp[0].attrs).type != INT)
            {
              EXITFAIL("Types missmatch. Integers required");
            }

            write_greater(FPASM_NAME, (yyvsp[-2].attrs).is_var, (yyvsp[0].attrs).is_var, tags++);
            (yyval.attrs).type = BOOLEAN;
            (yyval.attrs).is_var = false;
          }
#line 2340 "y.tab.c"
    break;

  case 73:
#line 1007 "alfa/alfa.y"
          {
            PRINT_RULE("<constante> ::= <constante_logica>", 99);
          }
#line 2348 "y.tab.c"
    break;

  case 74:
#line 1016 "alfa/alfa.y"
          {
            PRINT_RULE("<constante> ::= <constante_entera>", 100);
            (yyval.attrs).type = (yyvsp[0].attrs).type;
            (yyval.attrs).is_var = (yyvsp[0].attrs).is_var;
          }
#line 2358 "y.tab.c"
    break;

  case 75:
#line 1027 "alfa/alfa.y"
          {
            PRINT_RULE("<constante_logica> ::= true", 102);
          }
#line 2366 "y.tab.c"
    break;

  case 76:
#line 1036 "alfa/alfa.y"
          {
            PRINT_RULE("<constante_logica> ::= false", 103);
          }
#line 2374 "y.tab.c"
    break;

  case 77:
#line 1045 "alfa/alfa.y"
            {
              PRINT_RULE("<constante_entera> ::= TOK_CONSTANTE_ENTERA", 104);
              (yyval.attrs).type = INT;
              (yyval.attrs).is_var = false;
              (yyval.attrs).int_value = (yyvsp[0].attrs).int_value;
              /* push */
              snprintf(__buff, MAX_LEN, "%d", (yyvsp[0].attrs).int_value);
              write_operand(FPASM_NAME, __buff, false);
            }
#line 2388 "y.tab.c"
    break;

  case 78:
#line 1060 "alfa/alfa.y"
          {
            PRINT_RULE("<identificador> ::= TOK_IDENTIFICADOR", 108);
            if(st_searchCurrentScope(st, (yyvsp[0].attrs).lexeme) != NULL)
            {
              EXITFAIL("Identifier %s already at current scope", (yyvsp[0].attrs).lexeme);
            }
            else
            {
              st_insertBlindCurrentScope(
                st,
                (yyvsp[0].attrs).lexeme,
                current_category,
                current_type,
                current_class,
                current_scope,
                current_param_pos,
                current_var_pos,
                current_size,
                current_params,
                current_localvars
              );
            }
          }
#line 2416 "y.tab.c"
    break;


#line 2420 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
      yyerror (st, YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (st, yymsgp);
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
                      yytoken, &yylval, st);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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
                  yystos[yystate], yyvsp, st);
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
  yyerror (st, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, st);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, st);
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
#line 1085 "alfa/alfa.y"


/* User functions definitions */

int yyerror(SymbolsTable *st, char *s)
{
  if(morfofailure)
  {
    return PARSEFAIL;
  }
  
  COPYERR("Syntactic error: %s", s);
  
  return PARSEFAIL;
}

void write_symbols_table(FPASM, SymbolsTable *st)
{
  hash_iterator *iterator;
  iterator_node *__inode;
  Symbol *__s;
  int32_t size;
  
  if(!FPASM_NAME || !st)
    return;

  iterator = hash_iterate(st_getScopeHash(st));
  if(!iterator)
    return;
  
  if(!first(iterator))
    return;

  for(__inode = first(iterator); __inode != NULL; __inode = next(__inode))
  {
    __s = (Symbol*)iter_nodeInfo(__inode);

    if(symbol_get_category(__s) != VAR)
      continue;
    if(symbol_get_var_identifierCategory(__s) == SCALAR)
    {
      write_var_declaration(FPASM_NAME, symbol_get_key(__s), SCALAR, 1);
    }
    else
    {
      size = symbol_get_var_size(__s);
      write_var_declaration(FPASM_NAME, symbol_get_key(__s), VECTOR, size);
    }
  }
  
  hash_iterate_clean(iterator);
}
