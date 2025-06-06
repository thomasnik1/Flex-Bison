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
%token COMMENT
%token ERROR
%token EQUALS

%%

program:
    OPEN_MYHTML {printf("<MYHTML>\n");} content CLOSE_MYHTML { printf("Valid myHTML document.\n"); }
;

content:
    head_opt body
;

head_opt:
    /* empty */
    | head
;

head:
    OPEN_HEAD {printf("<head>\n");} title meta_opt CLOSE_HEAD
;

title:
    OPEN_TITLE TEXT {printf("%s",strbuf(str,strlen));} CLOSE_TITLE {
        if (strlen($2) > MAX_TITLE_LEN) {
            yyerror("Title exceeds 60 characters");
        }
    }
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
    TEXT image
    |image
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
    ID_ATTR EQUALS QUOTED_STRING {
        if (!is_unique_id($3)) yyerror("Duplicate ID");
        else {
            add_element_id($3);
            add_input_id($3);
        }
    }
    | STYLE_ATTR EQUALS QUOTED_STRING {
        if (!is_valid_style($3)) yyerror("Invalid style attribute");
    }
    | HREF_ATTR EQUALS QUOTED_STRING {
        if (!is_valid_url($3)) yyerror("Invalid href URL");
    }
    | SRC_ATTR EQUALS QUOTED_STRING {
        if (!is_valid_url($3)) yyerror("Invalid src URL");
    }
    | TYPE_ATTR EQUALS QUOTED_STRING {
        if (strcmp($3, "submit") == 0) {
            submit_input_count++;
            if (submit_input_count > 1) yyerror("Only one submit input allowed");
        } else if (strcmp($3, "text") != 0 && strcmp($3, "checkbox") != 0 && strcmp($3, "radio") != 0) {
            yyerror("Invalid type attribute");
        }
    }
    | FOR_ATTR EQUALS QUOTED_STRING {
        if (!input_id_exists($3)) yyerror("'for' must reference a valid input id");
    }
    | NAME_ATTR EQUALS QUOTED_STRING
    | VALUE_ATTR EQUALS QUOTED_STRING
    | ALT_ATTR EQUALS QUOTED_STRING
    | WIDTH_ATTR EQUALS NUMBER
    | HEIGHT_ATTR EQUALS NUMBER
    | CONTENT_ATTR EQUALS QUOTED_STRING
    | CHARSET_ATTR EQUALS QUOTED_STRING
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