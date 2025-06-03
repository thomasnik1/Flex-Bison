%{
#include "bison.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

"<!--([^><-]|(-[^->])|(\n))*-->"   { return COMMENT; }

"<MYHTML>"      { return OPEN_MYHTML; }
"</MYHTML>"     { return CLOSE_MYHTML; }
"<head>"        { return OPEN_HEAD; }
"</head>"       { return CLOSE_HEAD; }
"<body>"        { return OPEN_BODY; }
"</body>"       { return CLOSE_BODY; }

"<title>"       { return OPEN_TITLE; }
"</title>"      { return CLOSE_TITLE; }
"<meta"         { return OPEN_META; }
">"             { return TAG_CLOSE; }

"<p"            { return OPEN_P; }
"</p>"          { return CLOSE_P; }
"<a"            { return OPEN_A; }
"</a>"          { return CLOSE_A; }
"<img"          { return OPEN_IMG; }
"<form"         { return OPEN_FORM; }
"</form>"       { return CLOSE_FORM; }
"<input"        { return OPEN_INPUT; }
"<label"        { return OPEN_LABEL; }
"</label>"      { return CLOSE_LABEL; }
"<div"          { return OPEN_DIV; }
"</div>"        { return CLOSE_DIV; }

id              { return ID_ATTR; }
style           { return STYLE_ATTR; }
href            { return HREF_ATTR; }
src             { return SRC_ATTR; }
alt             { return ALT_ATTR; }
width           { return WIDTH_ATTR; }
height          { return HEIGHT_ATTR; }
type            { return TYPE_ATTR; }
value           { return VALUE_ATTR; }
for             { return FOR_ATTR; }
name            { return NAME_ATTR; }
content         { return CONTENT_ATTR; }
charset         { return CHARSET_ATTR; }

[a-zA-Z_]+   { yylval.str = strdup(yytext); return TEXT; }

\"[^\"]*\"      { yylval.str = strdup(yytext); return QUOTED_STRING; }
\'[^\']*\'      { yylval.str = strdup(yytext); return QUOTED_STRING; }

[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }

[ \t\n\r]+      ; // skip whitespace

.               { printf("Unknown character: %s\n", yytext); return ERROR; }


%%

int yywrap() {
    return 1;
}

void yyerror(const char* err){
    fprintf(stderr, "[ERROR - LINE %d] %s\n",yylineno, err);
    exit(EXIT_FAILURE);
}
