#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 2048
#define MAX_TOKENS 1000

static const char FILE_PATH[] = "examples/valid/return_3.c";

enum TokenType {
    OPEN_BRACE = 1,
    CLOSE_BRACE,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    SEMICOLON,
    INT_KEYWORD,
    RETURN_KEYWORD,
    IDENTIFIER,
    INTEGER_LITERAL_DECIMAL,
    INTEGER_LITERAL_HEXA,
    UNKNOWN
};

const char* get_token_type(enum TokenType type) 
{
   switch (type) 
   {
        case CLOSE_BRACE: return "CLOSE_BRACE";
        case OPEN_PARENTHESIS: return "OPEN_PARENTHESIS";
        case CLOSE_PARENTHESIS: return "CLOSE_PARENTHESIS";
        case SEMICOLON: return "SEMICOLON";
        case INT_KEYWORD: return "INT_KEYWORD";
        case RETURN_KEYWORD: return "RETURN_KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case INTEGER_LITERAL_DECIMAL: return "INTEGER_LITERAL_DECIMAL";
        case INTEGER_LITERAL_HEXA: return "INTEGER_LITERAL_HEXA";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNDEFINED";
   }
}

typedef struct token_data {
    char *token_text;
    int token_type;
    struct token_data *next;
} Token;

Token *createToken(char *s) {
    Token *newToken = (Token *)malloc(sizeof(Token));
    newToken->token_text = s;
    newToken->next = NULL;
    return newToken;
}


void insert(Token **link, Token *newToken) {
    newToken->next = *link;
    *link = newToken;
}

void printTokens(Token *head) {
    while (head != NULL) {
        printf("%s  ->  %s\n", head->token_text, get_token_type(head->token_type));
        head = head->next;
    }
}


int is_space(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}


int is_special(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
           c == ']' || c == ',' || c == ';' || c == '+' || c == '-';
}


int is_digit(char c) {
    return isdigit(c);
}


int is_letter(char c) {
    return isalpha(c);
}

int is_double_quotes(char c) {
    return c == '"';
}

int is_underscore(char c) {
    return c == '_';
}

int is_hexa(char *s, int size) {
    if (size < 3) {
        return 0;
    }

    if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) {
        return 0;
    }

    for (int i = 2; i < size; i++) {
        if (!isxdigit(s[i])) {
            return 0;
        } 
    }

    return 1;
}

int is_identifier(char *s, int size) {
    if (size < 1) {
        return 0;
    }

    if (!is_letter(s[0] && !is_underscore(s[0]))) {
        return 0;
    }

    for (int i = 1; i < size; i++) {
        if (!is_digit(s[i]) && !is_letter(s[i]) && !is_underscore(s[i])) {
            return 0;
        } 
    }

    return 1;
}





int main(void)
{
    FILE *file;
    char c;

    Token *head = NULL;
    Token *tail = NULL;
    Token *t;

    int token_count = 0;
    char **strings;
    strings = malloc(MAX_TOKENS * sizeof (char *));

    int length;

    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;

    int in_digit = 0;
    int in_quotes = 0;
    int in_identifier = 0;

    file = fopen(FILE_PATH, "r");

    t = createToken("root");
    insert(&head, t);
    tail = t;

    while (1) {
        // next character in file
        c = fgetc(file);
        
        // quit when end-of-file
        if (feof(file)) {
            break;
        }

        // operations
        if (in_digit) {
            ;
        }
        else if (in_quotes) {
            ;
        } 
        else if (in_identifier) {
            ;
        }
        else {
            ;
        }


        // append character to buffer
        buffer[buffer_pos++] = c;
        buffer[buffer_pos] = '\0';

        // allocate memory for string and copy buffer into it
        length = strlen(buffer);
        strings[token_count] = malloc(length*sizeof(char));
        strcpy(strings[token_count], buffer);

        // create token as linked list pointing to the saved strings
        t = createToken(strings[token_count++]);
        insert(&tail->next, t);
        tail = t;
    }

    fclose(file);

    printf("\n\n");
    printTokens(head);

    for (int i = 0; i < MAX_TOKENS; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
