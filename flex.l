%{
#include "bison.tab.h"
#include <string.h>
#include <stdlib.h>

extern int yylineno;
%}

%x IN_TAG 

%%

"<!--"([^><-]|(-[^->])|(\n))*"-->"   { return COMMENT; }

<INITIAL>"<MYHTML>"      { return OPEN_MYHTML; }
<INITIAL>"</MYHTML>"     { return CLOSE_MYHTML; }
<INITIAL>"<head>"        { return OPEN_HEAD; }
<INITIAL>"</head>"       { return CLOSE_HEAD; }
<INITIAL>"<body>"        { return OPEN_BODY; }
<INITIAL>"</body>"       { return CLOSE_BODY; }

<INITIAL>"<title>"       { return OPEN_TITLE; }
<INITIAL>"</title>"      { return CLOSE_TITLE; }

<INITIAL>"<meta"[ \t\n\r]      { BEGIN(IN_TAG); return OPEN_META; }

<INITIAL>"<p"[ \t\n\r]*        { BEGIN(IN_TAG); return OPEN_P; }
<INITIAL>"</p>"                { return CLOSE_P; }

<INITIAL>"<a"[ \t\n\r]*        { BEGIN(IN_TAG); return OPEN_A; }
<INITIAL>"</a>"                { return CLOSE_A; }

<INITIAL>"<img"[ \t\n\r]*     { BEGIN(IN_TAG); return OPEN_IMG; }

<INITIAL>"<form"[ \t\n\r]*     { BEGIN(IN_TAG); return OPEN_FORM; }
<INITIAL>"</form>"             { return CLOSE_FORM; }

<INITIAL>"<input"[ \t\n\r]*    { BEGIN(IN_TAG); return OPEN_INPUT; }

<INITIAL>"<label"[ \t\n\r]*    { BEGIN(IN_TAG); return OPEN_LABEL; }
<INITIAL>"</label>"            { return CLOSE_LABEL; }

<INITIAL>"<div"[ \t\n\r]*      { BEGIN(IN_TAG); return OPEN_DIV; }
<INITIAL>"</div>"              { return CLOSE_DIV; }

<IN_TAG>">"                    { BEGIN(INITIAL); return TAG_CLOSE; }
<IN_TAG>"="                    { return EQUALS; }

<IN_TAG>"id"              { return ID_ATTR; }
<IN_TAG>"style"           { return STYLE_ATTR; }
<IN_TAG>"href"            { return HREF_ATTR; }
<IN_TAG>"src"             { return SRC_ATTR; }
<IN_TAG>"alt"             { return ALT_ATTR; }
<IN_TAG>"width"           { return WIDTH_ATTR; }
<IN_TAG>"height"          { return HEIGHT_ATTR; }
<IN_TAG>"type"            { return TYPE_ATTR; }
<IN_TAG>"value"           { return VALUE_ATTR; }
<IN_TAG>"for"             { return FOR_ATTR; }
<IN_TAG>"name"            { return NAME_ATTR; }
<IN_TAG>"content"         { return CONTENT_ATTR; }
<IN_TAG>"charset"         { return CHARSET_ATTR; }


<IN_TAG>\"[^\"]*\"      {
    yylval.str = strdup(yytext + 1);
    yylval.str[strlen(yylval.str) - 1] = 0;  
    return QUOTED_STRING;
}

<IN_TAG>\'[^\']*\'      {
    yylval.str = strdup(yytext + 1);
    yylval.str[strlen(yylval.str) - 1] = 0;
    return QUOTED_STRING;
}

<IN_TAG>[0-9]+          {
    yylval.num = atoi(yytext);
    return NUMBER;
}

\n { yylineno++;}; 
[ \t\r]+ ;

<INITIAL>[^<>\n]+   {
    printf("OK \n");
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

