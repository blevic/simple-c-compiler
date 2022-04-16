#ifndef LEXER_H
#define LEXER_H

#define BUFFER_SIZE 2048
#define MAX_TOKENS 1000

static const char FILE_PATHS[][50] = {"examples/invalid/missing_paren.c",
                                      "examples/invalid/missing_retval.c",
                                      "examples/invalid/no_brace.c",
                                      "examples/invalid/no_semicolon.c",
                                      "examples/invalid/no_space.c",
                                      "examples/invalid/wrong_case.c",
                                      "examples/valid/multi_digit.c",
                                      "examples/valid/newlines.c",
                                      "examples/valid/no_newlines.c",
                                      "examples/valid/return_0.c",
                                      "examples/valid/return_2.c",
                                      "examples/valid/return_3.c"};

typedef struct token_data {
    char *token_text;
    int token_type;
    struct token_data *next;
} Token;


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

Token* tokenize(const char *file_path);

#endif