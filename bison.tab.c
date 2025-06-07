/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bison.y"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int yylex(void);
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

#define MAX_TITLE_LEN 60
#define MAX_STYLE_PROPERTIES 20

typedef struct {
    char* id;
} Element;

Element elements[100];
int element_count = 0;

char* input_ids[100];
int input_id_count = 0;

int submit_input_count = 0;
int last_input_line = 0;

int is_unique_id(const char* id) {
    for (int i = 0; i < element_count; i++) {
        if (strcmp(elements[i].id, id) == 0) return 0;
    }
    return 1;
}

void add_element_id(const char* id) {
    elements[element_count++].id = strdup(id);
}

void add_input_id(const char* id) {
    input_ids[input_id_count++] = strdup(id);
}

int input_id_exists(const char* id) {
    for (int i = 0; i < input_id_count; i++) {
        if (strcmp(input_ids[i], id) == 0) return 1;
    }
    return 0;
}

int is_valid_url(const char* url) {
    const char* pattern = "^[^[:space:]]+$";
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) return 0;
    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

int is_valid_style(const char* style) {
    char* temp = strdup(style);
    char* token = strtok(temp, ";");
    char* properties[MAX_STYLE_PROPERTIES];
    int count = 0;

    while (token && count < MAX_STYLE_PROPERTIES) {
        while (*token == ' ') token++;
        char* colon = strchr(token, ':');
        if (!colon) { free(temp); return 0; }
        *colon = '\0';
        char* prop = token;
        char* val = colon + 1;

        for (int i = 0; i < count; i++) {
            if (strcmp(properties[i], prop) == 0) { free(temp); return 0; }
        }
        properties[count++] = strdup(prop);

        if (strcmp(prop, "background_color") == 0 ||
            strcmp(prop, "color") == 0 ||
            strcmp(prop, "font_family") == 0) {
            // assume valid
        } else if (strcmp(prop, "font_size") == 0) {
            regex_t regex;
            regcomp(&regex, "^[1-9][0-9]*(px|%)$", REG_EXTENDED);
            if (regexec(&regex, val, 0, NULL, 0)) {
                free(temp); return 0;
            }
            regfree(&regex);
        } else {
            free(temp); return 0;
        }
        token = strtok(NULL, ";");
    }
    free(temp);
    return 1;
}

void yyerror(const char *err) {
    fprintf(stderr, "Error (line %d): %s at symbol '%s'\n", yylineno, err, yytext);
}

#line 174 "bison.tab.c"

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

#include "bison.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TEXT = 3,                       /* TEXT  */
  YYSYMBOL_QUOTED_STRING = 4,              /* QUOTED_STRING  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_OPEN_MYHTML = 6,                /* OPEN_MYHTML  */
  YYSYMBOL_CLOSE_MYHTML = 7,               /* CLOSE_MYHTML  */
  YYSYMBOL_OPEN_HEAD = 8,                  /* OPEN_HEAD  */
  YYSYMBOL_CLOSE_HEAD = 9,                 /* CLOSE_HEAD  */
  YYSYMBOL_OPEN_BODY = 10,                 /* OPEN_BODY  */
  YYSYMBOL_CLOSE_BODY = 11,                /* CLOSE_BODY  */
  YYSYMBOL_OPEN_TITLE = 12,                /* OPEN_TITLE  */
  YYSYMBOL_CLOSE_TITLE = 13,               /* CLOSE_TITLE  */
  YYSYMBOL_OPEN_META = 14,                 /* OPEN_META  */
  YYSYMBOL_OPEN_P = 15,                    /* OPEN_P  */
  YYSYMBOL_CLOSE_P = 16,                   /* CLOSE_P  */
  YYSYMBOL_OPEN_A = 17,                    /* OPEN_A  */
  YYSYMBOL_CLOSE_A = 18,                   /* CLOSE_A  */
  YYSYMBOL_OPEN_IMG = 19,                  /* OPEN_IMG  */
  YYSYMBOL_OPEN_FORM = 20,                 /* OPEN_FORM  */
  YYSYMBOL_CLOSE_FORM = 21,                /* CLOSE_FORM  */
  YYSYMBOL_OPEN_INPUT = 22,                /* OPEN_INPUT  */
  YYSYMBOL_OPEN_LABEL = 23,                /* OPEN_LABEL  */
  YYSYMBOL_CLOSE_LABEL = 24,               /* CLOSE_LABEL  */
  YYSYMBOL_OPEN_DIV = 25,                  /* OPEN_DIV  */
  YYSYMBOL_CLOSE_DIV = 26,                 /* CLOSE_DIV  */
  YYSYMBOL_ID_ATTR = 27,                   /* ID_ATTR  */
  YYSYMBOL_STYLE_ATTR = 28,                /* STYLE_ATTR  */
  YYSYMBOL_HREF_ATTR = 29,                 /* HREF_ATTR  */
  YYSYMBOL_SRC_ATTR = 30,                  /* SRC_ATTR  */
  YYSYMBOL_ALT_ATTR = 31,                  /* ALT_ATTR  */
  YYSYMBOL_WIDTH_ATTR = 32,                /* WIDTH_ATTR  */
  YYSYMBOL_HEIGHT_ATTR = 33,               /* HEIGHT_ATTR  */
  YYSYMBOL_TYPE_ATTR = 34,                 /* TYPE_ATTR  */
  YYSYMBOL_VALUE_ATTR = 35,                /* VALUE_ATTR  */
  YYSYMBOL_FOR_ATTR = 36,                  /* FOR_ATTR  */
  YYSYMBOL_NAME_ATTR = 37,                 /* NAME_ATTR  */
  YYSYMBOL_CONTENT_ATTR = 38,              /* CONTENT_ATTR  */
  YYSYMBOL_CHARSET_ATTR = 39,              /* CHARSET_ATTR  */
  YYSYMBOL_TAG_CLOSE = 40,                 /* TAG_CLOSE  */
  YYSYMBOL_ERROR = 41,                     /* ERROR  */
  YYSYMBOL_EQUALS = 42,                    /* EQUALS  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_content = 46,                   /* content  */
  YYSYMBOL_head_opt = 47,                  /* head_opt  */
  YYSYMBOL_head = 48,                      /* head  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_title = 50,                     /* title  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_52_4 = 52,                      /* $@4  */
  YYSYMBOL_meta_opt = 53,                  /* meta_opt  */
  YYSYMBOL_meta_list = 54,                 /* meta_list  */
  YYSYMBOL_meta = 55,                      /* meta  */
  YYSYMBOL_56_5 = 56,                      /* $@5  */
  YYSYMBOL_body = 57,                      /* body  */
  YYSYMBOL_58_6 = 58,                      /* $@6  */
  YYSYMBOL_body_elements_opt = 59,         /* body_elements_opt  */
  YYSYMBOL_body_elements = 60,             /* body_elements  */
  YYSYMBOL_element = 61,                   /* element  */
  YYSYMBOL_paragraph = 62,                 /* paragraph  */
  YYSYMBOL_63_7 = 63,                      /* $@7  */
  YYSYMBOL_64_8 = 64,                      /* $@8  */
  YYSYMBOL_65_9 = 65,                      /* $@9  */
  YYSYMBOL_anchor = 66,                    /* anchor  */
  YYSYMBOL_67_10 = 67,                     /* $@10  */
  YYSYMBOL_68_11 = 68,                     /* $@11  */
  YYSYMBOL_anchor_content = 69,            /* anchor_content  */
  YYSYMBOL_70_12 = 70,                     /* $@12  */
  YYSYMBOL_image = 71,                     /* image  */
  YYSYMBOL_72_13 = 72,                     /* $@13  */
  YYSYMBOL_form = 73,                      /* form  */
  YYSYMBOL_74_14 = 74,                     /* $@14  */
  YYSYMBOL_75_15 = 75,                     /* $@15  */
  YYSYMBOL_form_content = 76,              /* form_content  */
  YYSYMBOL_form_element = 77,              /* form_element  */
  YYSYMBOL_input = 78,                     /* input  */
  YYSYMBOL_79_16 = 79,                     /* $@16  */
  YYSYMBOL_label = 80,                     /* label  */
  YYSYMBOL_81_17 = 81,                     /* $@17  */
  YYSYMBOL_82_18 = 82,                     /* $@18  */
  YYSYMBOL_83_19 = 83,                     /* $@19  */
  YYSYMBOL_division = 84,                  /* division  */
  YYSYMBOL_85_20 = 85,                     /* $@20  */
  YYSYMBOL_86_21 = 86,                     /* $@21  */
  YYSYMBOL_attr_list_opt = 87,             /* attr_list_opt  */
  YYSYMBOL_attr_list = 88,                 /* attr_list  */
  YYSYMBOL_attribute = 89,                 /* attribute  */
  YYSYMBOL_90_22 = 90,                     /* $@22  */
  YYSYMBOL_91_23 = 91,                     /* $@23  */
  YYSYMBOL_92_24 = 92,                     /* $@24  */
  YYSYMBOL_93_25 = 93,                     /* $@25  */
  YYSYMBOL_94_26 = 94,                     /* $@26  */
  YYSYMBOL_95_27 = 95,                     /* $@27  */
  YYSYMBOL_96_28 = 96,                     /* $@28  */
  YYSYMBOL_97_29 = 97,                     /* $@29  */
  YYSYMBOL_98_30 = 98,                     /* $@30  */
  YYSYMBOL_99_31 = 99,                     /* $@31  */
  YYSYMBOL_100_32 = 100,                   /* $@32  */
  YYSYMBOL_101_33 = 101,                   /* $@33  */
  YYSYMBOL_102_34 = 102,                   /* $@34  */
  YYSYMBOL_103_35 = 103,                   /* $@35  */
  YYSYMBOL_104_36 = 104,                   /* $@36  */
  YYSYMBOL_105_37 = 105,                   /* $@37  */
  YYSYMBOL_106_38 = 106,                   /* $@38  */
  YYSYMBOL_107_39 = 107,                   /* $@39  */
  YYSYMBOL_108_40 = 108,                   /* $@40  */
  YYSYMBOL_109_41 = 109,                   /* $@41  */
  YYSYMBOL_110_42 = 110,                   /* $@42  */
  YYSYMBOL_111_43 = 111,                   /* $@43  */
  YYSYMBOL_112_44 = 112,                   /* $@44  */
  YYSYMBOL_113_45 = 113,                   /* $@45  */
  YYSYMBOL_114_46 = 114,                   /* $@46  */
  YYSYMBOL_115_47 = 115,                   /* $@47  */
  YYSYMBOL_116_48 = 116,                   /* $@48  */
  YYSYMBOL_117_49 = 117,                   /* $@49  */
  YYSYMBOL_118_50 = 118,                   /* $@50  */
  YYSYMBOL_119_51 = 119                    /* $@51  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       0,   130,   130,   130,   134,   137,   139,   143,   143,   147,
     147,   147,   155,   157,   161,   162,   166,   166,   170,   170,
     173,   175,   179,   180,   184,   184,   184,   184,   184,   188,
     188,   188,   188,   192,   192,   192,   196,   196,   197,   201,
     201,   205,   205,   205,   209,   210,   214,   214,   218,   218,
     222,   222,   222,   222,   226,   226,   226,   229,   231,   235,
     236,   240,   240,   240,   240,   247,   247,   247,   250,   250,
     250,   250,   253,   253,   253,   253,   256,   256,   256,   264,
     264,   264,   264,   267,   267,   267,   268,   268,   268,   269,
     269,   269,   270,   270,   270,   271,   271,   271,   272,   272,
     272,   273,   273,   273
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TEXT",
  "QUOTED_STRING", "NUMBER", "OPEN_MYHTML", "CLOSE_MYHTML", "OPEN_HEAD",
  "CLOSE_HEAD", "OPEN_BODY", "CLOSE_BODY", "OPEN_TITLE", "CLOSE_TITLE",
  "OPEN_META", "OPEN_P", "CLOSE_P", "OPEN_A", "CLOSE_A", "OPEN_IMG",
  "OPEN_FORM", "CLOSE_FORM", "OPEN_INPUT", "OPEN_LABEL", "CLOSE_LABEL",
  "OPEN_DIV", "CLOSE_DIV", "ID_ATTR", "STYLE_ATTR", "HREF_ATTR",
  "SRC_ATTR", "ALT_ATTR", "WIDTH_ATTR", "HEIGHT_ATTR", "TYPE_ATTR",
  "VALUE_ATTR", "FOR_ATTR", "NAME_ATTR", "CONTENT_ATTR", "CHARSET_ATTR",
  "TAG_CLOSE", "ERROR", "EQUALS", "$accept", "program", "$@1", "content",
  "head_opt", "head", "$@2", "title", "$@3", "$@4", "meta_opt",
  "meta_list", "meta", "$@5", "body", "$@6", "body_elements_opt",
  "body_elements", "element", "paragraph", "$@7", "$@8", "$@9", "anchor",
  "$@10", "$@11", "anchor_content", "$@12", "image", "$@13", "form",
  "$@14", "$@15", "form_content", "form_element", "input", "$@16", "label",
  "$@17", "$@18", "$@19", "division", "$@20", "$@21", "attr_list_opt",
  "attr_list", "attribute", "$@22", "$@23", "$@24", "$@25", "$@26", "$@27",
  "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35", "$@36",
  "$@37", "$@38", "$@39", "$@40", "$@41", "$@42", "$@43", "$@44", "$@45",
  "$@46", "$@47", "$@48", "$@49", "$@50", "$@51", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   -94,    46,    39,   -94,   -94,    41,    83,   -94,    37,
     -94,   -94,   -94,   -94,    81,    77,    95,   -94,    90,    81,
     -94,   -94,   -94,   -94,   -94,   -94,    92,    77,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,    52,   -94,   -94,    52,    52,
      52,    52,    52,   -94,   -94,    88,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -16,
     -94,    64,    52,     0,    24,    65,    67,   -94,    66,    69,
      70,    71,    72,    73,    74,    75,    76,    78,    79,    80,
      82,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   106,     7,    22,    77,   115,   119,   121,   122,   123,
     124,   125,   127,   128,   129,   130,   131,   132,   -94,   -94,
     110,   -94,   -94,   -94,    20,   -94,   -94,   -94,   111,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   126,   120,   -94,    52,    52,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,    38,    98,   -94,   -94,
     137,   -94,   117,   -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     2,     0,     5,     1,     7,     0,     0,     6,     0,
       3,    18,     4,     9,    12,    20,     0,    16,     0,    13,
      14,    29,    33,    39,    41,    54,     0,    21,    22,    24,
      25,    26,    27,    28,    10,     0,     8,    15,    57,     0,
       0,    57,    57,    19,    23,     0,    61,    65,    68,    72,
      89,    92,    95,    76,    86,    79,    83,    98,   101,     0,
      59,     0,    58,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    60,    30,    34,    40,    42,    55,    62,    66,
      69,    73,    90,    93,    96,    77,    87,    80,    84,    99,
     102,     0,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    36,
       0,    38,    48,    50,     0,    44,    46,    47,     0,    63,
      67,    70,    74,    91,    94,    97,    78,    88,    81,    85,
     100,   103,     0,     0,    35,     0,    57,    43,    45,    56,
      64,    71,    75,    82,    32,    37,     0,     0,    49,    51,
       0,    52,     0,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   133,   -94,   -94,   -94,    40,   -94,   116,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -93,   -94,
     -94,   -94,   -94,   -94,    21,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -40,   -35,   -56,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     6,     7,     8,     9,    14,    16,    45,
      18,    19,    20,    35,    12,    15,    26,    27,    28,    29,
      38,   101,   142,    30,    39,   102,   120,   143,    31,    40,
      32,    41,   103,   124,   125,   126,   145,   127,   146,   160,
     162,    33,    42,   104,    61,    62,    60,    68,   105,   150,
      69,   106,    70,   107,   151,    71,   108,   152,    75,   112,
      77,   114,   153,    78,   115,    76,   113,    72,   109,    73,
     110,    74,   111,    79,   116,    80,   117
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    65,    66,    82,    63,    64,    82,    82,    82,   121,
     119,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    81,     1,    23,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      84,   147,   122,   123,   122,   123,     4,     5,    10,    13,
     155,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    85,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,   158,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    21,    11,    22,    17,    23,    24,    34,    36,
      82,    67,    25,    43,    83,    86,   157,    87,    88,   118,
     156,    89,    90,    91,    92,    93,    94,    95,    96,   129,
      97,    98,    99,   130,   100,   131,   132,   133,   144,   134,
     135,   136,   137,   138,   139,   140,   141,   149,   159,    23,
     161,   163,   154,    44,   128,   148,     0,     0,     0,     0,
       0,     0,    37
};

static const yytype_int16 yycheck[] =
{
      35,    41,    42,    59,    39,    40,    62,    63,    64,   102,
       3,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     6,    19,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    21,    22,    23,    22,    23,     0,     8,     7,    12,
     143,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    15,    10,    17,    14,    19,    20,     3,     9,
     156,    13,    25,    11,    40,    40,   146,    40,    42,     3,
     145,    42,    42,    42,    42,    42,    42,    42,    42,     4,
      42,    42,    42,     4,    42,     4,     4,     4,    18,     5,
       5,     4,     4,     4,     4,     4,     4,    26,    40,    19,
       3,    24,    16,    27,   104,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    44,    45,     0,     8,    46,    47,    48,    49,
       7,    10,    57,    12,    50,    58,    51,    14,    53,    54,
      55,    15,    17,    19,    20,    25,    59,    60,    61,    62,
      66,    71,    73,    84,     3,    56,     9,    55,    63,    67,
      72,    74,    85,    11,    61,    52,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    88,
      89,    87,    88,    88,    88,    87,    87,    13,    90,    93,
      95,    98,   110,   112,   114,   101,   108,   103,   106,   116,
     118,    40,    89,    40,    40,    40,    40,    40,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    64,    68,    75,    86,    91,    94,    96,    99,   111,
     113,   115,   102,   109,   104,   107,   117,   119,     3,     3,
      69,    71,    22,    23,    76,    77,    78,    80,    59,     4,
       4,     4,     4,     4,     5,     5,     4,     4,     4,     4,
       4,     4,    65,    70,    18,    79,    81,    21,    77,    26,
      92,    97,   100,   105,    16,    71,    88,    87,    40,    40,
      82,     3,    83,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    45,    44,    46,    47,    47,    49,    48,    51,
      52,    50,    53,    53,    54,    54,    56,    55,    58,    57,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    63,
      64,    65,    62,    67,    68,    66,    70,    69,    69,    72,
      71,    74,    75,    73,    76,    76,    77,    77,    79,    78,
      81,    82,    83,    80,    85,    86,    84,    87,    87,    88,
      88,    90,    91,    92,    89,    93,    94,    89,    95,    96,
      97,    89,    98,    99,   100,    89,   101,   102,    89,   103,
     104,   105,    89,   106,   107,    89,   108,   109,    89,   110,
     111,    89,   112,   113,    89,   114,   115,    89,   116,   117,
      89,   118,   119,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     2,     0,     1,     0,     5,     0,
       0,     5,     0,     1,     1,     2,     0,     4,     0,     4,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     0,
       0,     0,     8,     0,     0,     7,     0,     3,     1,     0,
       4,     0,     0,     7,     1,     2,     1,     1,     0,     4,
       0,     0,     0,     8,     0,     0,     7,     0,     1,     1,
       2,     0,     0,     0,     6,     0,     0,     5,     0,     0,
       0,     6,     0,     0,     0,     6,     0,     0,     5,     0,
       0,     0,     6,     0,     0,     5,     0,     0,     5,     0,
       0,     5,     0,     0,     5,     0,     0,     5,     0,     0,
       5,     0,     0,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* $@1: %empty  */
#line 130 "bison.y"
                {printf("<MYHTML>\n");}
#line 1409 "bison.tab.c"
    break;

  case 3: /* program: OPEN_MYHTML $@1 content CLOSE_MYHTML  */
#line 130 "bison.y"
                                                             { printf("</MYHTML>\nValid myHTML document.\n"); }
#line 1415 "bison.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 143 "bison.y"
              {printf("<head>\n");}
#line 1421 "bison.tab.c"
    break;

  case 8: /* head: OPEN_HEAD $@2 title meta_opt CLOSE_HEAD  */
#line 143 "bison.y"
                                                              {printf("</head>\n");}
#line 1427 "bison.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 147 "bison.y"
               {printf("<title>");}
#line 1433 "bison.tab.c"
    break;

  case 10: /* $@4: %empty  */
#line 147 "bison.y"
                                          {printf("%s",yylval.str);}
#line 1439 "bison.tab.c"
    break;

  case 11: /* title: OPEN_TITLE $@3 TEXT $@4 CLOSE_TITLE  */
#line 147 "bison.y"
                                                                                 {
        if (strlen((yyvsp[-2].str)) > MAX_TITLE_LEN) {
            yyerror("Title exceeds 60 characters");
        }
        else printf("</title>\n");
    }
#line 1450 "bison.tab.c"
    break;

  case 16: /* $@5: %empty  */
#line 166 "bison.y"
              {printf("<meta ");}
#line 1456 "bison.tab.c"
    break;

  case 17: /* meta: OPEN_META $@5 attr_list TAG_CLOSE  */
#line 166 "bison.y"
                                                      {printf(">\n");}
#line 1462 "bison.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 170 "bison.y"
              {printf("<body>\n");}
#line 1468 "bison.tab.c"
    break;

  case 19: /* body: OPEN_BODY $@6 body_elements_opt CLOSE_BODY  */
#line 170 "bison.y"
                                                                 {printf("</body>\n");}
#line 1474 "bison.tab.c"
    break;

  case 29: /* $@7: %empty  */
#line 188 "bison.y"
           {printf("<p ");}
#line 1480 "bison.tab.c"
    break;

  case 30: /* $@8: %empty  */
#line 188 "bison.y"
                                                    {printf(">\n");}
#line 1486 "bison.tab.c"
    break;

  case 31: /* $@9: %empty  */
#line 188 "bison.y"
                                                                          {printf("%s",yylval.str);}
#line 1492 "bison.tab.c"
    break;

  case 32: /* paragraph: OPEN_P $@7 attr_list_opt TAG_CLOSE $@8 TEXT $@9 CLOSE_P  */
#line 188 "bison.y"
                                                                                                             {printf("</p>\n");}
#line 1498 "bison.tab.c"
    break;

  case 33: /* $@10: %empty  */
#line 192 "bison.y"
           {printf("<a ");}
#line 1504 "bison.tab.c"
    break;

  case 34: /* $@11: %empty  */
#line 192 "bison.y"
                                                {printf(">\n");}
#line 1510 "bison.tab.c"
    break;

  case 35: /* anchor: OPEN_A $@10 attr_list TAG_CLOSE $@11 anchor_content CLOSE_A  */
#line 192 "bison.y"
                                                                                        {printf("</a>\n");}
#line 1516 "bison.tab.c"
    break;

  case 36: /* $@12: %empty  */
#line 196 "bison.y"
         {printf("%s",yylval.str);}
#line 1522 "bison.tab.c"
    break;

  case 39: /* $@13: %empty  */
#line 201 "bison.y"
             {printf("<img ");}
#line 1528 "bison.tab.c"
    break;

  case 40: /* image: OPEN_IMG $@13 attr_list TAG_CLOSE  */
#line 201 "bison.y"
                                                    {printf(">\n");}
#line 1534 "bison.tab.c"
    break;

  case 41: /* $@14: %empty  */
#line 205 "bison.y"
              {printf("<form ");}
#line 1540 "bison.tab.c"
    break;

  case 42: /* $@15: %empty  */
#line 205 "bison.y"
                                                          {printf(">\n");}
#line 1546 "bison.tab.c"
    break;

  case 43: /* form: OPEN_FORM $@14 attr_list_opt TAG_CLOSE $@15 form_content CLOSE_FORM  */
#line 205 "bison.y"
                                                                                                   {printf("</form>\n");}
#line 1552 "bison.tab.c"
    break;

  case 48: /* $@16: %empty  */
#line 218 "bison.y"
               {printf("<input ");}
#line 1558 "bison.tab.c"
    break;

  case 49: /* input: OPEN_INPUT $@16 attr_list TAG_CLOSE  */
#line 218 "bison.y"
                                                        {printf(">\n");}
#line 1564 "bison.tab.c"
    break;

  case 50: /* $@17: %empty  */
#line 222 "bison.y"
                {printf("<label ");}
#line 1570 "bison.tab.c"
    break;

  case 51: /* $@18: %empty  */
#line 222 "bison.y"
                                                            {printf(">\n");}
#line 1576 "bison.tab.c"
    break;

  case 52: /* $@19: %empty  */
#line 222 "bison.y"
                                                                                  {printf("%s",yylval.str);}
#line 1582 "bison.tab.c"
    break;

  case 53: /* label: OPEN_LABEL $@17 attr_list_opt TAG_CLOSE $@18 TEXT $@19 CLOSE_LABEL  */
#line 222 "bison.y"
                                                                                                                         {printf("</label>\n");}
#line 1588 "bison.tab.c"
    break;

  case 54: /* $@20: %empty  */
#line 226 "bison.y"
             {printf("<div ");}
#line 1594 "bison.tab.c"
    break;

  case 55: /* $@21: %empty  */
#line 226 "bison.y"
                                                        {printf(">\n");}
#line 1600 "bison.tab.c"
    break;

  case 56: /* division: OPEN_DIV $@20 attr_list_opt TAG_CLOSE $@21 body_elements_opt CLOSE_DIV  */
#line 226 "bison.y"
                                                                                                     {printf("</div>\n");}
#line 1606 "bison.tab.c"
    break;

  case 61: /* $@22: %empty  */
#line 240 "bison.y"
            {printf("id");}
#line 1612 "bison.tab.c"
    break;

  case 62: /* $@23: %empty  */
#line 240 "bison.y"
                                   {printf("=");}
#line 1618 "bison.tab.c"
    break;

  case 63: /* $@24: %empty  */
#line 240 "bison.y"
                                                                {printf("\"%s\"",yylval.str);}
#line 1624 "bison.tab.c"
    break;

  case 64: /* attribute: ID_ATTR $@22 EQUALS $@23 QUOTED_STRING $@24  */
#line 240 "bison.y"
                                                                                              {
        if (!is_unique_id((yyvsp[-1].str))) yyerror("Duplicate ID");
        else {
            add_element_id((yyvsp[-1].str));
            add_input_id((yyvsp[-1].str));
        }
    }
#line 1636 "bison.tab.c"
    break;

  case 65: /* $@25: %empty  */
#line 247 "bison.y"
                 {printf("style");}
#line 1642 "bison.tab.c"
    break;

  case 66: /* $@26: %empty  */
#line 247 "bison.y"
                                           {printf("=");}
#line 1648 "bison.tab.c"
    break;

  case 67: /* attribute: STYLE_ATTR $@25 EQUALS $@26 QUOTED_STRING  */
#line 247 "bison.y"
                                                                        {{printf("\"%s\"",yylval.str);}
        if (!is_valid_style((yyvsp[0].str))) yyerror("Invalid style attribute");
    }
#line 1656 "bison.tab.c"
    break;

  case 68: /* $@27: %empty  */
#line 250 "bison.y"
                {printf("href");}
#line 1662 "bison.tab.c"
    break;

  case 69: /* $@28: %empty  */
#line 250 "bison.y"
                                         {printf("=");}
#line 1668 "bison.tab.c"
    break;

  case 70: /* $@29: %empty  */
#line 250 "bison.y"
                                                                      {printf("\"%s\"",yylval.str);}
#line 1674 "bison.tab.c"
    break;

  case 71: /* attribute: HREF_ATTR $@27 EQUALS $@28 QUOTED_STRING $@29  */
#line 250 "bison.y"
                                                                                                    {
        if (!is_valid_url((yyvsp[-1].str))) yyerror("Invalid href URL");
    }
#line 1682 "bison.tab.c"
    break;

  case 72: /* $@30: %empty  */
#line 253 "bison.y"
               {printf("src");}
#line 1688 "bison.tab.c"
    break;

  case 73: /* $@31: %empty  */
#line 253 "bison.y"
                                       {printf("=");}
#line 1694 "bison.tab.c"
    break;

  case 74: /* $@32: %empty  */
#line 253 "bison.y"
                                                                    {printf("\"%s\"",yylval.str);}
#line 1700 "bison.tab.c"
    break;

  case 75: /* attribute: SRC_ATTR $@30 EQUALS $@31 QUOTED_STRING $@32  */
#line 253 "bison.y"
                                                                                                  {
        if (!is_valid_url((yyvsp[-1].str))) yyerror("Invalid src URL");
    }
#line 1708 "bison.tab.c"
    break;

  case 76: /* $@33: %empty  */
#line 256 "bison.y"
                {printf("type");}
#line 1714 "bison.tab.c"
    break;

  case 77: /* $@34: %empty  */
#line 256 "bison.y"
                                         {printf("=");}
#line 1720 "bison.tab.c"
    break;

  case 78: /* attribute: TYPE_ATTR $@33 EQUALS $@34 QUOTED_STRING  */
#line 256 "bison.y"
                                                                      {{printf("\"%s\"",yylval.str);}
        if (strcmp((yyvsp[0].str), "submit") == 0) {
            submit_input_count++;
            if (submit_input_count > 1) yyerror("Only one submit input allowed");
        } else if (strcmp((yyvsp[0].str), "text") != 0 && strcmp((yyvsp[0].str), "checkbox") != 0 && strcmp((yyvsp[0].str), "radio") != 0) {
            yyerror("Invalid type attribute");
        }
    }
#line 1733 "bison.tab.c"
    break;

  case 79: /* $@35: %empty  */
#line 264 "bison.y"
               {printf("for");}
#line 1739 "bison.tab.c"
    break;

  case 80: /* $@36: %empty  */
#line 264 "bison.y"
                                       {printf("=");}
#line 1745 "bison.tab.c"
    break;

  case 81: /* $@37: %empty  */
#line 264 "bison.y"
                                                                    {printf("\"%s\"",yylval.str);}
#line 1751 "bison.tab.c"
    break;

  case 82: /* attribute: FOR_ATTR $@35 EQUALS $@36 QUOTED_STRING $@37  */
#line 264 "bison.y"
                                                                                                  {
        if (!input_id_exists((yyvsp[-1].str))) yyerror("'for' must reference a valid input id");
    }
#line 1759 "bison.tab.c"
    break;

  case 83: /* $@38: %empty  */
#line 267 "bison.y"
                {printf("name");}
#line 1765 "bison.tab.c"
    break;

  case 84: /* $@39: %empty  */
#line 267 "bison.y"
                                         {printf("=");}
#line 1771 "bison.tab.c"
    break;

  case 85: /* attribute: NAME_ATTR $@38 EQUALS $@39 QUOTED_STRING  */
#line 267 "bison.y"
                                                                      {printf("\"%s\"",yylval.str);}
#line 1777 "bison.tab.c"
    break;

  case 86: /* $@40: %empty  */
#line 268 "bison.y"
                 {printf("value");}
#line 1783 "bison.tab.c"
    break;

  case 87: /* $@41: %empty  */
#line 268 "bison.y"
                                           {printf("=");}
#line 1789 "bison.tab.c"
    break;

  case 88: /* attribute: VALUE_ATTR $@40 EQUALS $@41 QUOTED_STRING  */
#line 268 "bison.y"
                                                                        {printf("\"%s\"",yylval.str);}
#line 1795 "bison.tab.c"
    break;

  case 89: /* $@42: %empty  */
#line 269 "bison.y"
                {printf("alt");}
#line 1801 "bison.tab.c"
    break;

  case 90: /* $@43: %empty  */
#line 269 "bison.y"
                                       {printf("=");}
#line 1807 "bison.tab.c"
    break;

  case 91: /* attribute: ALT_ATTR $@42 EQUALS $@43 QUOTED_STRING  */
#line 269 "bison.y"
                                                                    {printf("\"%s\"",yylval.str);}
#line 1813 "bison.tab.c"
    break;

  case 92: /* $@44: %empty  */
#line 270 "bison.y"
                 {printf("width");}
#line 1819 "bison.tab.c"
    break;

  case 93: /* $@45: %empty  */
#line 270 "bison.y"
                                           {printf("=");}
#line 1825 "bison.tab.c"
    break;

  case 94: /* attribute: WIDTH_ATTR $@44 EQUALS $@45 NUMBER  */
#line 270 "bison.y"
                                                                 {printf("%d",yylval.num);}
#line 1831 "bison.tab.c"
    break;

  case 95: /* $@46: %empty  */
#line 271 "bison.y"
                  {printf("height");}
#line 1837 "bison.tab.c"
    break;

  case 96: /* $@47: %empty  */
#line 271 "bison.y"
                                             {printf("=");}
#line 1843 "bison.tab.c"
    break;

  case 97: /* attribute: HEIGHT_ATTR $@46 EQUALS $@47 NUMBER  */
#line 271 "bison.y"
                                                                   {printf("%d",yylval.num);}
#line 1849 "bison.tab.c"
    break;

  case 98: /* $@48: %empty  */
#line 272 "bison.y"
                   {printf("content");}
#line 1855 "bison.tab.c"
    break;

  case 99: /* $@49: %empty  */
#line 272 "bison.y"
                                               {printf("=");}
#line 1861 "bison.tab.c"
    break;

  case 100: /* attribute: CONTENT_ATTR $@48 EQUALS $@49 QUOTED_STRING  */
#line 272 "bison.y"
                                                                            {printf("\"%s\"",yylval.str);}
#line 1867 "bison.tab.c"
    break;

  case 101: /* $@50: %empty  */
#line 273 "bison.y"
                   {printf("charset");}
#line 1873 "bison.tab.c"
    break;

  case 102: /* $@51: %empty  */
#line 273 "bison.y"
                                              {printf("=");}
#line 1879 "bison.tab.c"
    break;

  case 103: /* attribute: CHARSET_ATTR $@50 EQUALS $@51 QUOTED_STRING  */
#line 273 "bison.y"
                                                                          {printf("\"%s\"",yylval.str);}
#line 1885 "bison.tab.c"
    break;


#line 1889 "bison.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 276 "bison.y"


int main(int argc, char **argv){
    if (argc > 1){
        FILE *file = fopen(argv[1], "r");
        if(!file){
            perror("could not open file");
            return 1;
        }
        yyin = file;
    }
    yyparse();
    return 0;
}
