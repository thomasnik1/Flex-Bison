%{
#include "bison.tab.h"
#include <string.h>
#include <stdlib.h>

extern int yylineno;
%}

%%

"<!--"([^><-]|(-[^->])|(\n))*"-->"   { return COMMENT; }

"="     { return EQUALS; }

"<MYHTML>"      { return OPEN_MYHTML; }
"</MYHTML>"     { return CLOSE_MYHTML; }
"<head>"        { return OPEN_HEAD; }
"</head>"       { return CLOSE_HEAD; }
"<body>"        { return OPEN_BODY; }
"</body>"       { return CLOSE_BODY; }

"<title"       { return OPEN_TITLE; }
"</title>"      { return CLOSE_TITLE; }
"<meta"       { return OPEN_META; }

"<p"[ \t\n\r]*          { return OPEN_P; }
"</p>"          { return CLOSE_P; }

"<a"[ \t\n\r]*            { return OPEN_A; }
"</a>"          { return CLOSE_A; }

"<img"[ \t\n\r]*          { return OPEN_IMG; }

"<form"[ \t\n\r]*        { return OPEN_FORM; }
"</form>"       { return CLOSE_FORM; }

"<input"[ \t\n\r]*        { return OPEN_INPUT; }

"<label"[ \t\n\r]*        { return OPEN_LABEL; }
"</label>"      { return CLOSE_LABEL; }

"<div"[ \t\n\r]*          { return OPEN_DIV; }
"</div>"        { return CLOSE_DIV; }

">"             { return TAG_CLOSE; }


"id"              { return ID_ATTR; }
"style"           { return STYLE_ATTR; }
"href"            { return HREF_ATTR; }
"src"             { return SRC_ATTR; }
"alt"             { return ALT_ATTR; }
"width"           { return WIDTH_ATTR; }
"height"          { return HEIGHT_ATTR; }
"type"            { return TYPE_ATTR; }
"value"           { return VALUE_ATTR; }
"for"             { return FOR_ATTR; }
"name"            { return NAME_ATTR; }
"content"         { return CONTENT_ATTR; }
"charset"         { return CHARSET_ATTR; }


\"[^\"]*\"      {
    yylval.str = strdup(yytext + 1);
    yylval.str[strlen(yylval.str) - 1] = 0;  
    return QUOTED_STRING;
}

\'[^\']*\'      {
    yylval.str = strdup(yytext + 1);
    yylval.str[strlen(yylval.str) - 1] = 0;
    return QUOTED_STRING;
}

[0-9]+          {
    yylval.num = atoi(yytext);
    return NUMBER;
}

\n { yylineno++;}; 
[ \t\r]+ ;

">"[\n]+[^<]+   {
    printf("OK ");
    yylval.str = strdup(yytext);
    return TEXT;
}

.               {
    fprintf(stderr, "Unknown character: %s (line %d)\n", yytext, yylineno);
    return ERROR;
}

%%

int yywrap() {
    return 1;
}

