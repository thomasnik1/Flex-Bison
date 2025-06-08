%{ 
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
%token TAG_CLOSE
%token ERROR
%token EQUALS

%%

myhtml:
    OPEN_MYHTML {printf("<MYHTML>\n");} head body CLOSE_MYHTML { printf("</MYHTML>\nValid myHTML document.\n"); }
;


head:
    /* empty */
    | OPEN_HEAD {printf("<head>\n");} title meta_list CLOSE_HEAD {printf("</head>\n");}
;

title:
    OPEN_TITLE {printf("<title>");}  TEXT {printf("%s",yylval.str);} CLOSE_TITLE {
        if (strlen($3) > MAX_TITLE_LEN) {
            yyerror("Title exceeds 60 characters");
        }
        else printf("</title>\n");
    }
;


meta_list:
    /* empty */
    | meta_list meta
;

meta:
    OPEN_META {printf("<meta ");} attr_list TAG_CLOSE {printf(">\n");}
;

body:
    OPEN_BODY {printf("<body>\n");} body_elements CLOSE_BODY {printf("</body>\n");}
;


body_elements:
    /* empty */
    | body_elements element
;

element:
    paragraph | anchor | image | form | division 
;

paragraph:
    OPEN_P {printf("<p ");} attr_list TAG_CLOSE {printf(">\n");} TEXT {printf("%s",yylval.str);} CLOSE_P {printf("</p>\n");}
;

anchor:
    OPEN_A {printf("<a ");} attr_list TAG_CLOSE {printf(">\n");} anchor_content CLOSE_A {printf("</a>\n");}
;

anchor_content:
    TEXT {printf("%s",yylval.str);} image
    |image
;

image:
    OPEN_IMG {printf("<img ");} attr_list TAG_CLOSE {printf(">\n");}
;

form:
    OPEN_FORM {printf("<form ");} attr_list TAG_CLOSE {printf(">\n");} form_content CLOSE_FORM {printf("</form>\n");}
;

form_content:
    form_element
    | form_content form_element
;

form_element:
    input | label
;

input:
    OPEN_INPUT {printf("<input ");} attr_list TAG_CLOSE {printf(">\n");}
;

label:
    OPEN_LABEL  {printf("<label ");}attr_list TAG_CLOSE {printf(">\n");} TEXT {printf("%s",yylval.str);} CLOSE_LABEL {printf("</label>\n");}
;

division:
    OPEN_DIV {printf("<div ");} attr_list TAG_CLOSE {printf(">\n");} body_elements CLOSE_DIV {printf("</div>\n");}
;

attr_list:
    /* empty */
    | attr_list attribute
;

attribute:
    ID_ATTR {printf("id");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}{
        if (!is_unique_id($5)) yyerror("Duplicate ID");
        else {
            add_element_id($5);
            add_input_id($5);
        }
    }
    | STYLE_ATTR {printf("style");} EQUALS {printf("=");} QUOTED_STRING {{printf("\"%s\"",yylval.str);}
        if (!is_valid_style($5)) yyerror("Invalid style attribute");
    }
    | HREF_ATTR {printf("href");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}{
        if (!is_valid_url($5)) yyerror("Invalid href URL");
    }
    | SRC_ATTR {printf("src");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}{
        if (!is_valid_url($5)) yyerror("Invalid src URL");
    }
    | TYPE_ATTR {printf("type");} EQUALS {printf("=");} QUOTED_STRING {{printf("\"%s\"",yylval.str);}
        if (strcmp($5, "submit") == 0) {
            submit_input_count++;
            if (submit_input_count > 1) yyerror("Only one submit input allowed");
        } else if (strcmp($5, "text") != 0 && strcmp($5, "checkbox") != 0 && strcmp($5, "radio") != 0) {
            yyerror("Invalid type attribute");
        }
    }
    | FOR_ATTR {printf("for");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}{
        if (!input_id_exists($5)) yyerror("'for' must reference a valid input id");
    }
    | NAME_ATTR {printf("name");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}
    | VALUE_ATTR {printf("value");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}
    | ALT_ATTR  {printf("alt");}EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}
    | WIDTH_ATTR {printf("width");} EQUALS {printf("=");} NUMBER {printf("%d",yylval.num);}
    | HEIGHT_ATTR {printf("height");} EQUALS {printf("=");} NUMBER {printf("%d",yylval.num);}
    | CONTENT_ATTR {printf("content");} EQUALS {printf("=");} QUOTED_STRING {printf("\"%s\"",yylval.str);}
    | CHARSET_ATTR {printf("charset");}EQUALS {printf("=");} QUOTED_STRING{printf("\"%s\"",yylval.str);}
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