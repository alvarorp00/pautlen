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
  #include <stdbool.h>
  #include "alfa.h"
  #include "symbolsTable.h"
  #include "generator.h"

  #define _PRINT_RULES_
  #ifdef _PRINT_RULES_
  #define PRINT_RULE(str, val) \
              fprintf(yyout, ";R%d:\t%s\n", val, str);
  #else
  #define PRINT_RULE(str, val)
  #endif
  
  #define PARSEFAIL 0

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

  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
  /* - - - - - - GLOBAL VARS - - - - - - - */
  /* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */

  ElementCategory current_category; /* VAR, PARAM, FUNCT */
  DataType current_type; /* INT, BOOLEAN */
  IdentifierCategory current_class; /* SCALAR, VECTOR */
  Scope current_scope; /* GLOBAL, LOCAL */
  int current_pos; /* Position inside funct either params or localvars */
  int8_t current_size; /* Vector's size */
  int32_t current_params; /* Function params amount */
  int32_t current_localvars; /* Function localvars amount */

  bool in_declare; /* true if we're in declarations part, false if not */
  

#line 127 "y.tab.c"

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
    TOK_CONSTANTE_ENTERA = 291,
    TOK_TRUE = 292,
    TOK_FALSE = 293,
    TOK_ERROR = 294,
    MENOSU = 295,
    TOK_CTE_ENTERA = 296,
    TOK_IDENTIFICADOR = 297
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
#define TOK_CONSTANTE_ENTERA 291
#define TOK_TRUE 292
#define TOK_FALSE 293
#define TOK_ERROR 294
#define MENOSU 295
#define TOK_CTE_ENTERA 296
#define TOK_IDENTIFICADOR 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 61 "alfa/alfa.y"

  attrs_type attrs;

#line 267 "y.tab.c"

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
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   135,   135,   146,   155,   163,   172,   181,   190,   200,
     210,   219,   229,   239,   248,   257,   266,   276,   284,   293,
     303,   311,   321,   329,   338,   348,   356,   365,   374,   383,
     392,   401,   410,   419,   428,   437,   447,   456,   465,   474,
     483,   492,   501,   510,   519,   528,   537,   546,   555,   564,
     573,   582,   591,   601,   610,   619,   628,   637,   646,   655,
     665,   673,   683,   691,   700,   709,   718,   727,   736,   745,
     754,   763,   772,   781,   791
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
  "TOK_MAYORIGUAL", "TOK_CONSTANTE_ENTERA", "TOK_TRUE", "TOK_FALSE",
  "TOK_ERROR", "MENOSU", "TOK_CTE_ENTERA", "TOK_IDENTIFICADOR", "$accept",
  "program", "er1", "er2", "declarations", "declaration", "class",
  "class_scalar", "type", "class_vector", "identifiers", "functions",
  "function", "function_params", "remaining_function_params",
  "function_param", "function_declarations", "statements", "statement",
  "simple_statement", "block", "assignment", "vector_element",
  "conditional", "loop", "reading", "writing", "function_return", "exp",
  "exp_list", "exp_remaining_list", "comparison", "constant",
  "constant_logic", "constant_int", "identifier", YY_NULLPTR
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
     295,   296,   297
};
# endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,     2,    28,    54,   -39,   -39,   -39,     5,   -39,    54,
     -13,   -39,   -39,   -39,    27,    25,   -39,   -39,    32,    34,
      26,     5,   -39,    25,   -39,   -13,   -39,    42,   -13,    23,
     -39,   -39,   -39,    48,    57,    59,   -13,    50,    50,    55,
      23,    63,   -39,   -39,    56,   -39,   -39,   -39,   -39,   -39,
     -11,     5,    50,    50,   -39,    50,    50,    50,   -39,   -39,
     -39,   148,   -39,   -39,   -39,    -2,   148,   -39,   -39,   -39,
      50,    50,    50,   -13,    65,    69,   130,   140,    99,    67,
     -39,   -39,    50,    50,    50,    50,    50,    50,    50,   148,
      18,   148,   -39,    74,     5,   -39,    75,    76,   -39,    50,
      50,    50,    50,    50,    50,   -39,   -21,   -21,   -39,   -39,
     -39,   -21,   120,    68,   -39,    54,    69,    23,    23,   148,
     148,   148,   148,   148,   148,    50,   -39,   -39,   -39,    23,
     -39,    77,    78,   120,    82,    88,   -39,   -39,   -39,    84,
      23,    85,   -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    11,    12,     0,     3,     5,
       0,     8,    10,     9,     0,    17,     6,    74,     0,    14,
       0,     0,     4,    17,     7,     0,    73,     0,     0,     0,
      16,    15,    13,     0,     0,     0,     0,     0,     0,     0,
      26,     0,    29,    30,     0,    34,    35,    31,    32,    33,
       0,    20,     0,     0,    42,     0,     0,     0,    71,    72,
      57,    43,    54,    69,    70,    53,    44,     2,    27,    28,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
      49,    52,     0,     0,     0,     0,     0,     0,    60,    37,
       0,    36,    23,     0,     0,    19,     0,     0,    55,     0,
       0,     0,     0,     0,     0,    56,    45,    46,    48,    47,
      50,    51,    62,     0,    38,    25,    22,     0,     0,    67,
      68,    63,    64,    65,    66,     0,    59,    58,    24,     0,
      21,     0,     0,    62,     0,    39,    41,    61,    18,     0,
       0,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   -39,   -39,    -6,   -39,   -39,   -39,     6,   -39,
      80,    87,   -39,   -39,    -5,    19,   -39,   -38,   -39,   -39,
     -39,   -39,   -28,   -39,   -39,   -39,   -39,   -39,   -32,   -39,
     -19,   -39,   -39,   -39,    95,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    15,    29,     8,     9,    10,    11,    12,    13,
      18,    22,    23,    74,    95,    75,   129,    39,    40,    41,
      42,    43,    60,    45,    46,    47,    48,    49,    61,   113,
     126,    79,    62,    63,    64,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      19,    44,    68,    16,    84,    85,    66,    71,    86,     5,
       6,    72,    44,    14,    88,    19,    71,     1,    33,    50,
      76,    77,     3,    78,    80,    81,    54,    28,     4,    17,
      50,    34,    21,    35,    36,    37,    38,   114,    89,    90,
      91,    82,    83,    84,    85,    20,    24,    86,    87,    25,
     106,   107,   108,   109,   110,   111,   112,    73,     5,     6,
       7,    32,    26,    92,    51,    17,    55,   119,   120,   121,
     122,   123,   124,    52,    56,    53,    67,    69,    70,   131,
     132,    57,    93,    94,   105,   127,    26,    58,    59,    44,
      44,   134,    17,   133,   115,   117,   118,   139,   135,   136,
      73,    44,   141,   138,   140,    31,   142,    50,    50,   128,
      30,   130,    44,   116,   137,    27,    98,     0,     0,    50,
       0,     0,    82,    83,    84,    85,    99,   100,    86,    87,
      50,   101,   102,   103,   104,   125,     0,     0,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    96,     0,    86,
      87,     0,     0,    82,    83,    84,    85,    97,     0,    86,
      87,     0,     0,    82,    83,    84,    85,     0,     0,    86,
      87,    82,    83,    84,    85,     0,     0,    86,    87
};

static const yytype_int16 yycheck[] =
{
      10,    29,    40,     9,    25,    26,    38,    18,    29,     4,
       5,    22,    40,     7,    16,    25,    18,     3,    28,    29,
      52,    53,    20,    55,    56,    57,    36,    21,     0,    42,
      40,     8,     7,    10,    11,    12,    13,    19,    70,    71,
      72,    23,    24,    25,    26,    18,    14,    29,    30,    15,
      82,    83,    84,    85,    86,    87,    88,    51,     4,     5,
       6,    19,    36,    73,    16,    42,    16,    99,   100,   101,
     102,   103,   104,    16,    24,    16,    21,    14,    22,   117,
     118,    31,    17,    14,    17,    17,    36,    37,    38,   117,
     118,   129,    42,   125,    20,    20,    20,     9,    21,    21,
      94,   129,   140,    21,    20,    25,    21,   117,   118,   115,
      23,   116,   140,    94,   133,    20,    17,    -1,    -1,   129,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
     140,    32,    33,    34,    35,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    17,    -1,    29,
      30,    -1,    -1,    23,    24,    25,    26,    17,    -1,    29,
      30,    -1,    -1,    23,    24,    25,    26,    -1,    -1,    29,
      30,    23,    24,    25,    26,    -1,    -1,    29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    44,    20,     0,     4,     5,     6,    47,    48,
      49,    50,    51,    52,    51,    45,    47,    42,    53,    78,
      18,     7,    54,    55,    14,    15,    36,    77,    51,    46,
      54,    53,    19,    78,     8,    10,    11,    12,    13,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      78,    16,    16,    16,    78,    16,    24,    31,    37,    38,
      65,    71,    75,    76,    77,    78,    71,    21,    60,    14,
      22,    18,    22,    51,    56,    58,    71,    71,    71,    74,
      71,    71,    23,    24,    25,    26,    29,    30,    16,    71,
      71,    71,    78,    17,    14,    57,    17,    17,    17,    27,
      28,    32,    33,    34,    35,    17,    71,    71,    71,    71,
      71,    71,    71,    72,    19,    20,    58,    20,    20,    71,
      71,    71,    71,    71,    71,    15,    73,    17,    47,    59,
      57,    60,    60,    71,    60,    21,    21,    73,    21,     9,
      20,    60,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    46,    47,    47,    48,    49,    49,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    56,
      56,    57,    57,    58,    59,    59,    60,    60,    61,    61,
      62,    62,    62,    62,    63,    63,    64,    64,    65,    66,
      66,    67,    68,    69,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    75,
      75,    76,    76,    77,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     0,     0,     1,     2,     3,     1,     1,
       1,     1,     1,     5,     1,     3,     2,     0,    10,     2,
       0,     3,     0,     2,     1,     0,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     7,
      11,     7,     2,     2,     2,     3,     3,     3,     3,     2,
       3,     3,     2,     1,     1,     3,     3,     1,     4,     2,
       0,     3,     0,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1
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
#line 136 "alfa/alfa.y"
      {
        PRINT_RULE("<programa> ::= main { <declaraciones> <funciones> <sentencias> }", 1);
        // write_end(FPASM_NAME);
      }
#line 1561 "y.tab.c"
    break;

  case 3:
#line 146 "alfa/alfa.y"
    {

    }
#line 1569 "y.tab.c"
    break;

  case 4:
#line 155 "alfa/alfa.y"
    {

    }
#line 1577 "y.tab.c"
    break;

  case 5:
#line 164 "alfa/alfa.y"
            {
              PRINT_RULE("<declaraciones> ::= <declaracion>", 2);
            }
#line 1585 "y.tab.c"
    break;

  case 6:
#line 173 "alfa/alfa.y"
            {
              PRINT_RULE("<declaraciones> ::= <declaracion> <declaraciones>", 3);
            }
#line 1593 "y.tab.c"
    break;

  case 7:
#line 182 "alfa/alfa.y"
          {
            PRINT_RULE("<declaracion> ::= <clase> <identificadores> ;", 4);
          }
#line 1601 "y.tab.c"
    break;

  case 8:
#line 191 "alfa/alfa.y"
      {
        // current_class = SCALAR;
        PRINT_RULE("<clase> ::= <clase_escalar>", 5);
      }
#line 1610 "y.tab.c"
    break;

  case 9:
#line 201 "alfa/alfa.y"
      {
        // current_class = VECTOR;
        PRINT_RULE("<clase> ::= <clase_vector>", 7);
      }
#line 1619 "y.tab.c"
    break;

  case 10:
#line 211 "alfa/alfa.y"
            {
              PRINT_RULE("<clase_escalar> ::= <tipo> ", 9);
            }
#line 1627 "y.tab.c"
    break;

  case 11:
#line 220 "alfa/alfa.y"
      {
        // current_type = INT;
        PRINT_RULE("<tipo> ::= int", 10);
      }
#line 1636 "y.tab.c"
    break;

  case 12:
#line 230 "alfa/alfa.y"
      {
        // current_type = BOOLEAN;
        PRINT_RULE("<tipo> ::= boolean", 11);
      }
#line 1645 "y.tab.c"
    break;

  case 13:
#line 240 "alfa/alfa.y"
            {
              PRINT_RULE("<clase_vector> ::= array <tipo> [ <constante_entera> ]", 15);
            }
#line 1653 "y.tab.c"
    break;

  case 14:
#line 249 "alfa/alfa.y"
          {
            PRINT_RULE("<identificadores> ::= <identificador>", 18);
          }
#line 1661 "y.tab.c"
    break;

  case 15:
#line 258 "alfa/alfa.y"
          {
            PRINT_RULE("<identificadores> ::= <identificador> , <identificadores>", 19);
          }
#line 1669 "y.tab.c"
    break;

  case 16:
#line 267 "alfa/alfa.y"
        {
          PRINT_RULE("<funciones> :: <funcion> <funciones>", 20);
        }
#line 1677 "y.tab.c"
    break;

  case 17:
#line 276 "alfa/alfa.y"
        {
          PRINT_RULE("<funciones> ::= ", 21);
        }
#line 1685 "y.tab.c"
    break;

  case 18:
#line 285 "alfa/alfa.y"
        {
          PRINT_RULE("<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }", 22);
        }
#line 1693 "y.tab.c"
    break;

  case 19:
#line 294 "alfa/alfa.y"
              {
                PRINT_RULE("<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>", 23);
              }
#line 1701 "y.tab.c"
    break;

  case 20:
#line 303 "alfa/alfa.y"
              {
                PRINT_RULE("<parametros_funcion> ::= ", 24);
              }
#line 1709 "y.tab.c"
    break;

  case 21:
#line 312 "alfa/alfa.y"
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>", 25);
                        }
#line 1717 "y.tab.c"
    break;

  case 22:
#line 321 "alfa/alfa.y"
                        {
                          PRINT_RULE("<resto_parametros_funcion> ::= ", 26);
                        }
#line 1725 "y.tab.c"
    break;

  case 23:
#line 330 "alfa/alfa.y"
              {
                PRINT_RULE("<parametro_funcion> ::= <tipo> <identificador>", 27);
              }
#line 1733 "y.tab.c"
    break;

  case 24:
#line 339 "alfa/alfa.y"
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= <declaraciones>", 28);
                    }
#line 1741 "y.tab.c"
    break;

  case 25:
#line 348 "alfa/alfa.y"
                    {
                      PRINT_RULE("<declaraciones_funcion> ::= ", 29);
                    }
#line 1749 "y.tab.c"
    break;

  case 26:
#line 357 "alfa/alfa.y"
          {
            PRINT_RULE("<sentencias> ::= <sentencia>", 30);
          }
#line 1757 "y.tab.c"
    break;

  case 27:
#line 366 "alfa/alfa.y"
          {
            PRINT_RULE("<sentencias> ::= <sentencia> <sentencias>", 31);
          }
#line 1765 "y.tab.c"
    break;

  case 28:
#line 375 "alfa/alfa.y"
        {
          PRINT_RULE("<sentencia> ::= <sentencia_simple> ;", 32);
        }
#line 1773 "y.tab.c"
    break;

  case 29:
#line 384 "alfa/alfa.y"
        {
          PRINT_RULE("<sentencia> ::= <bloque>", 33);
        }
#line 1781 "y.tab.c"
    break;

  case 30:
#line 393 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <asignacion>", 34);
              }
#line 1789 "y.tab.c"
    break;

  case 31:
#line 402 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <lectura>", 35);
              }
#line 1797 "y.tab.c"
    break;

  case 32:
#line 411 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <escritura>", 36);
              }
#line 1805 "y.tab.c"
    break;

  case 33:
#line 420 "alfa/alfa.y"
              {
                PRINT_RULE("<sentencia_simple> ::= <retorno_funcion>", 38);
              }
#line 1813 "y.tab.c"
    break;

  case 34:
#line 429 "alfa/alfa.y"
    {
      PRINT_RULE("<bloque> ::= <condicional>", 40);
    }
#line 1821 "y.tab.c"
    break;

  case 35:
#line 438 "alfa/alfa.y"
    {
      PRINT_RULE("<bloque> ::= <bubcle>", 41);
    }
#line 1829 "y.tab.c"
    break;

  case 36:
#line 448 "alfa/alfa.y"
    {
      PRINT_RULE("<asignacion> ::= <identificador> = <exp>", 43);
    }
#line 1837 "y.tab.c"
    break;

  case 37:
#line 457 "alfa/alfa.y"
    {
      PRINT_RULE("<asignacion> ::= <elemento_vector> = <exp>", 44);
    }
#line 1845 "y.tab.c"
    break;

  case 38:
#line 466 "alfa/alfa.y"
              {
                PRINT_RULE("<elemento_vector> ::= <identificador> [ <exp> ]", 48);
              }
#line 1853 "y.tab.c"
    break;

  case 39:
#line 475 "alfa/alfa.y"
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> }", 50);
          }
#line 1861 "y.tab.c"
    break;

  case 40:
#line 484 "alfa/alfa.y"
          {
            PRINT_RULE("<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }", 51);
          }
#line 1869 "y.tab.c"
    break;

  case 41:
#line 493 "alfa/alfa.y"
    {
      PRINT_RULE("<bucle> ::= whie ( <exp> ) { <sentencias> }", 52);
    }
#line 1877 "y.tab.c"
    break;

  case 42:
#line 502 "alfa/alfa.y"
      {
        PRINT_RULE("<lectura> ::= scanf <identificador>", 54);
      }
#line 1885 "y.tab.c"
    break;

  case 43:
#line 511 "alfa/alfa.y"
      {
        PRINT_RULE("<escritura> ::= printf <exp>", 56);
      }
#line 1893 "y.tab.c"
    break;

  case 44:
#line 520 "alfa/alfa.y"
      {
        PRINT_RULE("<retorno_funcion> ::= return <exp>", 61);
      }
#line 1901 "y.tab.c"
    break;

  case 45:
#line 529 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> + <exp>", 72);
    }
#line 1909 "y.tab.c"
    break;

  case 46:
#line 538 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> - <exp>", 73);
    }
#line 1917 "y.tab.c"
    break;

  case 47:
#line 547 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> / <exp>", 74);
    }
#line 1925 "y.tab.c"
    break;

  case 48:
#line 556 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> * <exp>", 75);
    }
#line 1933 "y.tab.c"
    break;

  case 49:
#line 565 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= - <exp>", 76);
    }
#line 1941 "y.tab.c"
    break;

  case 50:
#line 574 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> && <exp>", 77);
    }
#line 1949 "y.tab.c"
    break;

  case 51:
#line 583 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <exp> || <exp>", 78);
    }
#line 1957 "y.tab.c"
    break;

  case 52:
#line 592 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ! <exp>", 79);
    }
#line 1965 "y.tab.c"
    break;

  case 53:
#line 602 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <identificador>", 80);
    }
#line 1973 "y.tab.c"
    break;

  case 54:
#line 611 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <constante>", 81);
    }
#line 1981 "y.tab.c"
    break;

  case 55:
#line 620 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ( <exp> )", 82);
    }
#line 1989 "y.tab.c"
    break;

  case 56:
#line 629 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= ( <comparacion> )", 83);
    }
#line 1997 "y.tab.c"
    break;

  case 57:
#line 638 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <elemento_vector>", 85);
    }
#line 2005 "y.tab.c"
    break;

  case 58:
#line 647 "alfa/alfa.y"
    {
      PRINT_RULE("<exp> ::= <identificador> ( <lista_expresiones> )", 88);
    }
#line 2013 "y.tab.c"
    break;

  case 59:
#line 656 "alfa/alfa.y"
        {
          PRINT_RULE("<lista_expresiones> ::= <exp> <resto_lista_expresiones>", 89);
        }
#line 2021 "y.tab.c"
    break;

  case 60:
#line 665 "alfa/alfa.y"
        {
          PRINT_RULE("<lista_expresiones> ::= ", 90);
        }
#line 2029 "y.tab.c"
    break;

  case 61:
#line 674 "alfa/alfa.y"
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>", 91);
                  }
#line 2037 "y.tab.c"
    break;

  case 62:
#line 683 "alfa/alfa.y"
                  {
                    PRINT_RULE("<resto_lista_expresiones> ::= ", 92);
                  }
#line 2045 "y.tab.c"
    break;

  case 63:
#line 692 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> == <exp>", 93);
          }
#line 2053 "y.tab.c"
    break;

  case 64:
#line 701 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> != <exp>", 94);
          }
#line 2061 "y.tab.c"
    break;

  case 65:
#line 710 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> <= <exp>", 95);
          }
#line 2069 "y.tab.c"
    break;

  case 66:
#line 719 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> >= <exp>", 96);
          }
#line 2077 "y.tab.c"
    break;

  case 67:
#line 728 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> < <exp>", 97);
          }
#line 2085 "y.tab.c"
    break;

  case 68:
#line 737 "alfa/alfa.y"
          {
            PRINT_RULE("<comparacion> ::= <exp> > <exp>", 98);
          }
#line 2093 "y.tab.c"
    break;

  case 69:
#line 746 "alfa/alfa.y"
          {
            PRINT_RULE("<constante> ::= <constante_logica>", 99);
          }
#line 2101 "y.tab.c"
    break;

  case 70:
#line 755 "alfa/alfa.y"
          {
            PRINT_RULE("<constante> ::= <constante_entera>", 100);
          }
#line 2109 "y.tab.c"
    break;

  case 71:
#line 764 "alfa/alfa.y"
          {
            PRINT_RULE("<constante_logica> ::= true", 102);
          }
#line 2117 "y.tab.c"
    break;

  case 72:
#line 773 "alfa/alfa.y"
          {
            PRINT_RULE("<constante_logica> ::= false", 103);
          }
#line 2125 "y.tab.c"
    break;

  case 73:
#line 782 "alfa/alfa.y"
            {
              PRINT_RULE("<constante_entera> ::= TOK_CONSTANTE_ENTERA", 104);
              /* write_operand(FPASM_NAME, $1.int_value, false); */
            }
#line 2134 "y.tab.c"
    break;

  case 74:
#line 792 "alfa/alfa.y"
          {
            PRINT_RULE("<identificador> ::= TOK_IDENTIFICADOR", 108);
            /*if(st_searchCurrentScope(st, $1.lexeme) != NULL)
            {
              #line 743 "alfa.y"
              COPYERR(__FILE__, "Identifier %s already at current scope", $1.lexeme);
              return PARSEFAIL;
            }
            else
            {
              st_insertBlindCurrentScope(
                st,
                $1.lexeme,
                current_category,
                current_type,
                current_class,
                current_scope,
                current_pos,
                current_size,
                current_params,
                current_localvars
              );
            }*/
          }
#line 2163 "y.tab.c"
    break;


#line 2167 "y.tab.c"

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
#line 818 "alfa/alfa.y"


/* User functions definitions */

int yyerror(SymbolsTable *st, char *s)
{
  if(morfofailure)
  {
    return -1;
  }
  
  COPYERR("alfa.y", "Syntactic error: %s", s);
  
  return -1;
}
