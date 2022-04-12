#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

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
        printf("%s  ->  %d\n", head->token_text, head->token_type);
        head = head->next;
    }
}

int main(void)
{
    FILE *file;
    char c;

    Token *head = NULL;
    Token *tail = NULL;
    Token *n;

    file = fopen(FILE_PATH, "r");

    while (1) {
        c = fgetc(file);
 
        if (feof(file))
            break;
 
        printf("%c", c);
    }

    fclose(file);

    return 0;
}
