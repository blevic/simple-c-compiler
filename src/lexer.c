#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "lexer_aux.h"


const char* get_token_type(enum TokenType type) {
   switch (type) 
   {
        case OPEN_BRACE: return "OPEN_BRACE";
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


int map_token_type(char *s) {
    if (!strcmp(s, "{")) {
        return OPEN_BRACE;
    }
    else if (!strcmp(s, "}")) {
        return CLOSE_BRACE;
    } 
    else if (!strcmp(s, "(")) {
        return OPEN_PARENTHESIS;
    }
    else if (!strcmp(s, ")")) {
        return CLOSE_PARENTHESIS;
    }
    else if (!strcmp(s, ";")) {
        return SEMICOLON;
    }
    else if (!strcmp(s, "int")) {
        return INT_KEYWORD;
    }
    else if (!strcmp(s, "return")) {
        return RETURN_KEYWORD;
    }
    else if (is_identifier(s)) {
        return IDENTIFIER;
    }
    else if (is_decimal(s)) {
        return INTEGER_LITERAL_DECIMAL;
    }
    else if (is_hexa(s)) {
        return INTEGER_LITERAL_HEXA;
    }
    else {
        return UNKNOWN;
    }
}


Token *create_token(char *s) {
    Token *new_token = (Token *)malloc(sizeof(Token));
    new_token->token_text = s;
    new_token->token_type = map_token_type(s);
    new_token->next = NULL;
    return new_token;
}


void insert(Token **link, Token *new_token) {
    new_token->next = *link;
    *link = new_token;
}


void print_tokens(Token *head) {
    printf("\nTokens:\n");
    while (head != NULL) {
        printf("%s  ->  %s\n", head->token_text, get_token_type(head->token_type));
        head = head->next;
    }
}


Token *first_node(char *buf, char **strings, int i, Token *head) {
    strings[i] = malloc(strlen(buf)*sizeof(char));
    strcpy(strings[i], buf);

    Token* t = create_token(strings[i]);
    insert(&head, t);

    return t;
}


Token *append(char *buf, char **strings, int i, Token *tail) {
    strings[i] = malloc(strlen(buf)*sizeof(char));
    strcpy(strings[i], buf);

    Token* t = create_token(strings[i]);
    insert(&tail->next, t);

    return t;
}


void free_null_strings(char** strings) {
    for (int i = 0; i < MAX_TOKENS; i++) {
        if (strings[i] == NULL) {
            free(strings[i]);
        }
    }
}


void free_tokens(Token *head) {
    Token* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->token_text);
        free(tmp);
    }
}


Token* tokenize(const char *file_path) {
    FILE *file;
    char c;

    Token *head = NULL;
    Token *tail = NULL;

    int token_count = 0;
    char **strings;
    strings = malloc(MAX_TOKENS * sizeof (char *));

    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;
    buffer[buffer_pos] = '\0';

    int in_digit = 0;
    int in_quotes = 0;
    int in_identifier = 0;

    file = fopen(file_path, "r");

    head = first_node("", strings, token_count, head);
    tail = head;

    while (1) {
        c = fgetc(file);
        
        if (feof(file)) {
            break;
        }

        if (in_digit) {
            if (is_digit(c) || is_letter(c)) {
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';
            }
            else if (is_space(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
            }
            else if (is_double_quotes((c))) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
                in_quotes = 1;
            }
            else if (is_special(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
            }
            else {
                printf("Tokenizer (in-digit) got an unidentified character!\n");
                return tail->next;
            }
        }
        else if (in_quotes) {
            buffer[buffer_pos++] = c;
            buffer[buffer_pos] = '\0';
            if (is_double_quotes(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_quotes = 0;
            }
        } 
        else if (in_identifier) {
            if (is_digit(c) || is_letter(c) || is_underscore(c)) {
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';
            }
            else if (is_space(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
            }
            else if (is_double_quotes(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
                in_quotes = 1;
            }
            else if (is_special(c)) {
                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
            }
            else {
                printf("Tokenizer (in-identifier) got an unidentified character!\n");
                return tail->next;
            }
        }
        else {
            if (is_space(c)) {
                ;
            }
            else if (is_digit(c)) {
                in_digit = 1;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';
            }
            else if (is_double_quotes(c)) {
                in_quotes = 1;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';
            }
            else if (is_letter(c) || is_underscore(c)) {
                in_identifier = 1;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';
            }
            else if (is_special(c)) {
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                tail = append(buffer, strings, token_count++, tail);

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';
            }
            else {
                printf("Tokenizer (first-digit) got an unidentified character!\n");
                return tail->next;
            }
        }


    }

    if (buffer[buffer_pos] != '\0') {
        tail = append(buffer, strings, token_count++, tail);
    } 

    fclose(file);

    Token* tmp = head;
    head = head->next;
    
    free(tmp->token_text);
    free(tmp);

    free_null_strings(strings);

    return head;
}


int main() {
    int n_files =  sizeof(FILE_PATHS)/sizeof(FILE_PATHS[0]);

    for (int i = 0; i < n_files; i++){
        Token* head = tokenize(FILE_PATHS[i]);
        print_tokens(head);
        free_tokens(head);
    }

    return 0;
}
