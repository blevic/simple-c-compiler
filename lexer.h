#ifndef LEXER_H
#define LEXER_H

typedef struct token_data {
    char *token_text;
    int token_type;
    struct token_data *next;
} Token;

Token* tokenize(const char *);

#endif