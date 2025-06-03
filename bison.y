%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void); 
extern FILE *yyin;
extern char *yytext;
extern void yyerror(const char* err);
extern int yylineno;
    
%}

%union {
    char* str;
    int num;
}

%token <str> TEXT QUOTED_STRING
%token <num> NUMBER
%token OPEN_MYHTML CLOSE_MYHTML
%token OPEN_HEAD CLOSE_HEAD OPEN_BODY CLOSE_BODY
%token OPEN_TITLE CLOSE_TITLE
%token OPEN_META
%token OPEN_P CLOSE_P
%token OPEN_A CLOSE_A
%token OPEN_IMG
%token OPEN_FORM CLOSE_FORM
%token OPEN_INPUT
%token OPEN_LABEL CLOSE_LABEL
%token OPEN_DIV CLOSE_DIV
%token ID_ATTR STYLE_ATTR HREF_ATTR SRC_ATTR ALT_ATTR WIDTH_ATTR HEIGHT_ATTR TYPE_ATTR VALUE_ATTR FOR_ATTR NAME_ATTR CONTENT_ATTR CHARSET_ATTR
%token TAG_CLOSE COMMENT
%token ERROR

%%

program:
    OPEN_MYHTML content CLOSE_MYHTML { printf("Valid myHTML document.\n"); }
;

content:
    head_opt body
;

head_opt:
    /* empty */
    | head
;

head:
    OPEN_HEAD title meta_opt CLOSE_HEAD
;

meta_opt:
    /* empty */
    | meta_list
;

meta_list:
    meta
    | meta_list meta
;

meta:
    OPEN_META attr_list TAG_CLOSE
;

title:
    OPEN_TITLE TEXT CLOSE_TITLE
;

body:
    OPEN_BODY body_elements_opt CLOSE_BODY
;

body_elements_opt:
    /* empty */
    | body_elements
;

body_elements:
    element
    | body_elements element
;

element:
    paragraph | anchor | image | form | division | comment
;

paragraph:
    OPEN_P attr_list_opt TAG_CLOSE TEXT CLOSE_P
;

anchor:
    OPEN_A attr_list TAG_CLOSE anchor_content CLOSE_A
;

anchor_content:
    TEXT
    | image
;

image:
    OPEN_IMG attr_list TAG_CLOSE
;

form:
    OPEN_FORM attr_list_opt TAG_CLOSE form_content CLOSE_FORM
;

form_content:
    form_element
    | form_content form_element
;

form_element:
    input | label
;

input:
    OPEN_INPUT attr_list TAG_CLOSE
;

label:
    OPEN_LABEL attr_list_opt TAG_CLOSE TEXT CLOSE_LABEL
;

division:
    OPEN_DIV attr_list_opt TAG_CLOSE body_elements_opt CLOSE_DIV
;

comment:
    COMMENT
;

attr_list_opt:
    /* empty */
    | attr_list
;

attr_list:
    attribute
    | attr_list attribute
;

attribute:
    ID_ATTR '=' QUOTED_STRING
    | STYLE_ATTR '=' QUOTED_STRING
    | HREF_ATTR '=' QUOTED_STRING
    | SRC_ATTR '=' QUOTED_STRING
    | ALT_ATTR '=' QUOTED_STRING
    | WIDTH_ATTR '=' NUMBER
    | HEIGHT_ATTR '=' NUMBER
    | TYPE_ATTR '=' QUOTED_STRING
    | VALUE_ATTR '=' QUOTED_STRING
    | FOR_ATTR '=' QUOTED_STRING
    | NAME_ATTR '=' QUOTED_STRING
    | CONTENT_ATTR '=' QUOTED_STRING
    | CHARSET_ATTR '=' QUOTED_STRING
;

%%

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
