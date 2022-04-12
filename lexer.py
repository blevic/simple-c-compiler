from enum import Enum
from multiprocessing.dummy import Value


class TokenType(Enum):
    OPEN_BRACE = 1
    CLOSE_BRACE = 2
    OPEN_PARENTHESIS = 3
    CLOSE_PARENTHESIS = 4
    SEMICOLON = 5
    INT_KEYWORD = 6
    RETURN_KEYWORD = 7
    IDENTIFIER = 8
    INTEGER_LITERAL_DECIMAL = 9
    INTEGER_LITERAL_HEXA = 10
    UNKNOWN = 11


def is_space(c):
    return c.isspace()


def is_special(c):
    return c in ['(', ')', '{', '}', '[', ']', ',', ';', '+', '-']


def is_digit(c):
    return c.isdigit()


def is_letter(c):
    return c.isalpha()


def is_double_quotes(c):
    return c == '"'


def is_underscore(c):
    return c == '_'


def is_hexa(s):
    return len(s) > 2 and s[:2].lower() == '0x' and all(is_digit(c) or c.lower() in 'abcdef' for c in s[2:])


def is_identifier(s):
    return len(s) > 0 and (is_letter(s[0]) or is_underscore(s[0])) and all(is_letter(c) or is_digit(c) or is_underscore(c) for c in s[1:])


def tokenize(file_path):
    flat = ""

    with open(file_path, 'r') as file:
        for line in file:
            flat += line
    
    in_digit = False
    in_quotes = False
    in_identifier = False

    tokens = []
    buffer = ""

    for i in range(len(flat)):
        c = flat[i]
        if in_digit:
            if is_digit(c) or is_letter(c):
                buffer += c # lexical errors will be treated later
            elif is_space(c):
                tokens.append(buffer)
                buffer = ""
                in_digit = False
            elif is_double_quotes(c):
                tokens.append(buffer)
                buffer = c
                in_digit = False
                in_quotes = True
            elif is_special(c):
                tokens.append(buffer)
                buffer = ""
                tokens.append(c)
                in_digit = False
            else:
                raise ValueError("Tokenizer (in-digit) got an unidentified character!")
        elif in_quotes:
            if is_double_quotes(c):
                buffer += c
                tokens.append(buffer)
                buffer = ""
                in_quotes = False
            else:
                buffer += c
        elif in_identifier:
            if is_digit(c) or is_letter(c) or is_underscore(c):
                buffer += c
            elif is_space(c):
                tokens.append(buffer)
                buffer = ""
                in_identifier = False
            elif is_double_quotes(c):
                tokens.append(buffer)
                buffer = c
                in_identifier = False
                in_quotes = True
            elif is_special(c):
                tokens.append(buffer)
                buffer = ""
                tokens.append(c)
                in_identifier = False
            else:
                raise ValueError("Tokenizer (in-identifier) got an unidentified character!")
        else:
            if is_space(c):
                pass
            elif is_digit(c):
                in_digit = True
                buffer += c
            elif is_double_quotes(c):
                in_quotes = True
                buffer += c
            elif is_letter(c) or is_underscore(c):
                in_identifier = True
                buffer += c
            elif is_special(c):
                tokens.append(c)
            else:
                raise ValueError("Tokenizer (first-digit) got an unidentified character!")

    if buffer != "":
        tokens.append(buffer)
    return tokens


class Token:
    def __init__(self, token_text):
        self.text = token_text
        self.type = self.token_type()
    
    def token_type(self):
        if self.text == "{":
            return TokenType.OPEN_BRACE
        elif self.text == "}":
            return TokenType.CLOSE_BRACE
        elif self.text == "(":
            return TokenType.OPEN_PARENTHESIS
        elif self.text == ")":
            return TokenType.CLOSE_PARENTHESIS
        elif self.text == ";":
            return TokenType.SEMICOLON
        elif self.text == "int":
            return TokenType.INT_KEYWORD
        elif self.text == "return":
            return TokenType.RETURN_KEYWORD
        elif is_identifier(self.text):
            return TokenType.IDENTIFIER
        elif is_digit(self.text):
            return TokenType.INTEGER_LITERAL_DECIMAL
        elif is_hexa(self.text):
            return TokenType.INTEGER_LITERAL_HEXA
        else:
            return TokenType.UNKNOWN


def lex(file_path):
    return [Token(t) for t in tokenize(file_path)]


if __name__ == '__main__':
    file = "examples/valid/multi_digit.c"
    for e in lex(file):
        print(e.text, "  ->  " , e.type)
