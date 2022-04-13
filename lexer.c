#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 2048
#define MAX_TOKENS 1000

static const char FILE_PATH[] = "examples/valid/return_3.c";


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

int is_decimal(char *s, int size) {
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
    else if (is_identifier(s, strlen(s))) {
        return IDENTIFIER;
    }
    else if (is_decimal(s, strlen(s))) {
        return INTEGER_LITERAL_DECIMAL;
    }
    else if (is_hexa(s, strlen(s))) {
        return INTEGER_LITERAL_HEXA;
    }
    else {
        return UNKNOWN;
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
    newToken->token_type = map_token_type(s);
    newToken->next = NULL;
    return newToken;
}


void insert(Token **link, Token *newToken) {
    newToken->next = *link;
    *link = newToken;
}

void print_tokens(Token *head) {
    printf("\nTokens:\n");
    while (head != NULL) {
        printf("%s  ->  %s\n", head->token_text, get_token_type(head->token_type));
        head = head->next;
    }
}


int tokenize(const char *file_path) {
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
    buffer[buffer_pos] = '\0';

    int in_digit = 0;
    int in_quotes = 0;
    int in_identifier = 0;

    file = fopen(file_path, "r");

    t = createToken(".");
    insert(&head, t);
    tail = t;

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
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
            }
            else if (is_double_quotes((c))) {
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
                in_quotes = 1;
            }
            else if (is_special(c)) {
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_digit = 0;
            }
            else {
                printf("Tokenizer (in-digit) got an unidentified character!\n");
                return -1;
            }
        }
        else if (in_quotes) {
            buffer[buffer_pos++] = c;
            buffer[buffer_pos] = '\0';
            if (is_double_quotes(c)) {
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

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
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
            }
            else if (is_double_quotes(c)) {
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
                in_quotes = 1;
            }
            else if (is_special(c)) {
                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos++] = c;
                buffer[buffer_pos] = '\0';

                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';

                in_identifier = 0;
            }
            else {
                printf("Tokenizer (in-identifier) got an unidentified character!\n");
                return -1;
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

                length = strlen(buffer);
                strings[token_count] = malloc(length*sizeof(char));
                strcpy(strings[token_count], buffer);
                t = createToken(strings[token_count++]);
                insert(&tail->next, t);
                tail = t;

                buffer_pos = 0;
                buffer[buffer_pos] = '\0';
            }
            else {
                printf("Tokenizer (first-digit) got an unidentified character!\n");
                return -1;
            }
        }


    }

    if (buffer[buffer_pos] != '\0') {
        length = strlen(buffer);
        strings[token_count] = malloc(length*sizeof(char));
        strcpy(strings[token_count], buffer);
        t = createToken(strings[token_count++]);
        insert(&tail->next, t);
        tail = t;
    } 

    fclose(file);

    print_tokens(head);

    for (int i = 0; i < MAX_TOKENS; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}



int main(void)
{
    int result = tokenize(FILE_PATH);
    return 0;
}
