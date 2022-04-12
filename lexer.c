#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Token *t;

    int token_count = 0;
    char **strings;
    strings = malloc(MAX_TOKENS * sizeof (char *));

    int length;

    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;

    file = fopen(FILE_PATH, "r");

    t = createToken("ABC");
    insert(&head, t);
    tail = t;

    while (1) {
        // next character in file
        c = fgetc(file);
        
        // quit when end-of-file
        if (feof(file)) {
            break;
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
