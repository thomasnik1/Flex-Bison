/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TEXT = 258,                    /* TEXT  */
    QUOTED_STRING = 259,           /* QUOTED_STRING  */
    NUMBER = 260,                  /* NUMBER  */
    OPEN_MYHTML = 261,             /* OPEN_MYHTML  */
    CLOSE_MYHTML = 262,            /* CLOSE_MYHTML  */
    OPEN_HEAD = 263,               /* OPEN_HEAD  */
    CLOSE_HEAD = 264,              /* CLOSE_HEAD  */
    OPEN_BODY = 265,               /* OPEN_BODY  */
    CLOSE_BODY = 266,              /* CLOSE_BODY  */
    OPEN_TITLE = 267,              /* OPEN_TITLE  */
    CLOSE_TITLE = 268,             /* CLOSE_TITLE  */
    OPEN_META = 269,               /* OPEN_META  */
    OPEN_P = 270,                  /* OPEN_P  */
    CLOSE_P = 271,                 /* CLOSE_P  */
    OPEN_A = 272,                  /* OPEN_A  */
    CLOSE_A = 273,                 /* CLOSE_A  */
    OPEN_IMG = 274,                /* OPEN_IMG  */
    OPEN_FORM = 275,               /* OPEN_FORM  */
    CLOSE_FORM = 276,              /* CLOSE_FORM  */
    OPEN_INPUT = 277,              /* OPEN_INPUT  */
    OPEN_LABEL = 278,              /* OPEN_LABEL  */
    CLOSE_LABEL = 279,             /* CLOSE_LABEL  */
    OPEN_DIV = 280,                /* OPEN_DIV  */
    CLOSE_DIV = 281,               /* CLOSE_DIV  */
    ID_ATTR = 282,                 /* ID_ATTR  */
    STYLE_ATTR = 283,              /* STYLE_ATTR  */
    HREF_ATTR = 284,               /* HREF_ATTR  */
    SRC_ATTR = 285,                /* SRC_ATTR  */
    ALT_ATTR = 286,                /* ALT_ATTR  */
    WIDTH_ATTR = 287,              /* WIDTH_ATTR  */
    HEIGHT_ATTR = 288,             /* HEIGHT_ATTR  */
    TYPE_ATTR = 289,               /* TYPE_ATTR  */
    VALUE_ATTR = 290,              /* VALUE_ATTR  */
    FOR_ATTR = 291,                /* FOR_ATTR  */
    NAME_ATTR = 292,               /* NAME_ATTR  */
    CONTENT_ATTR = 293,            /* CONTENT_ATTR  */
    CHARSET_ATTR = 294,            /* CHARSET_ATTR  */
    TAG_CLOSE = 295,               /* TAG_CLOSE  */
    COMMENT = 296,                 /* COMMENT  */
    ERROR = 297,                   /* ERROR  */
    EQUALS = 298                   /* EQUALS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 104 "bison.y"

    char* str;
    int num;

#line 112 "bison.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
