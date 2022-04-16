#ifndef LEXER_AUX_H
#define LEXER_AUX_H

int is_space(char c);

int is_special(char c);

int is_digit(char c);

int is_letter(char c);

int is_double_quotes(char c);

int is_underscore(char c);

int is_hexa(char *s);

int is_identifier(char *s);

int is_decimal(char *s);

#endif