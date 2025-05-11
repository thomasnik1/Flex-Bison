%{
    //C declarations and headers

    #include <stdio.h>
    #include <stdlib.h>
    #include "bison.tab.h"

    void yyerror(const char* err);
    char str_buf[200];
%}

%Option noyywrap 
%option yylineno
%x COMMENT

integer [-+]?[0-9]+
string [^\"]+

%%

"\n" {printf("\n");}
"\t" {printf("\t");}
" " {printf(" ");}

"<" {return LESS_THAN;}
">" {return GREATER_THAN;}
":" {return COLON;}
"/" {return SLASH;}
"=" {return ASSIGN;}
"\"" {return BACKSLASH;}

"MYHTML" {return MYHTML;}
"id" {return ID;}
"head" {return HEAD;}
"body" {return BODY;}
"title" {return TITLE;}
"meta" {return META;}
"charset" {return CHARSET;}
"name" {return NAME;}
"content" {return CONTENT;}
"p" {return PARAGRAPH;}
"style" {return STYLE;}
"a" {return LINK;}
"img" {return IMAGE;}
"src" {return SOURCE;}
"alt" {return ALT;}
"width" {return WIDTH;}
"height" {return HEIGHT;}
"form" {return FORM;}
"input" {return INPUT;}
"label" {return LABEL;}
"type" {return TYPE;}
"value" {return VALUE;}
"div" {return CONTAINER;}
"for" {return FOR;}


\"{string}\" {yylval.strval=strdup(yytext); return STRING;}

"<!--" {printf("Comment found in line %d.\n",yylineno); strcpy(str_buf,""); BEGIN(COMMENT);}
<COMMENT>"-->" {BEGIN(INITIAL); printf("%s\n",str_buf);}
<COMMENT>. {strcat(str_buf,yytext);}


<<EOF>> {printf("\n\n\tSuccess.\n");return 0;}


%%

//Code
void yyerror(const char* err)
{
    fprintf(stderr, "[ERROR - LINE %d] %s\n",yylineno, err);
    exit(EXIT_FAILURE);
}
