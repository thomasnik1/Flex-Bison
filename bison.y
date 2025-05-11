%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern FILE *yyin;
    extern int yylex();
    extern int yylineno;
    extern char *yytext;
    extern void yyerror(const char* err);
%}

%union{
    int intval;
    char *strval;
    char charval;
}

%token LESS_THAN
%token GREATER_THAN
%token COLON
%token SLASH
%token ASSIGN
%token BACKSLASH
%token MYHTML
%token ID
%token HEAD
%token BODY
%token TITLE
%token META
%token CHARSET
%token NAME
%token CONTENT
%token PARAGRAPH
%token STYLE
%token LINK
%token IMAGE
%token SOURCE
%token ALT
%token WIDTH
%token HEIGHT
%token FORM
%token INPUT
%token LABEL
%token TYPE
%token VALUE
%token CONTAINER
%token FOR
%token <intval> INT
%token <strval> STRING

%%

input:
    | input item
    ;

item:
    MYHTML {printf("MYHTML token");}
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

