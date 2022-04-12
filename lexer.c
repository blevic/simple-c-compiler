#include <stdio.h>
#include <string.h>

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

int main(void)
{
    FILE *file;
    char c;

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
