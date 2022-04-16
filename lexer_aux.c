#include <string.h>
#include <ctype.h>
#include "lexer_aux.h"


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

int is_hexa(char *s) {
    int size = strlen(s);

    if (size < 3) {
        return 0;
    }

    if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) {
        return 0;
    }

    for (int i = 2; i < size; i++) {
        if (!is_digit(s[i])) {
            return 0;
        } 
    }

    return 1;
}

int is_identifier(char *s) {
    int size = strlen(s);

    if (size < 1) {
        return 0;
    }

    if (!is_letter(s[0]) && !is_underscore(s[0])) {
        return 0;
    }

    for (int i = 1; i < size; i++) {
        if (!is_digit(s[i]) && !is_letter(s[i]) && !is_underscore(s[i])) {
            return 0;
        } 
    }

    return 1;
}

int is_decimal(char *s) {
    int size = strlen(s);

    if (size < 1) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (!is_digit(s[i])) {
            return 0;
        } 
    }

    return 1;
}