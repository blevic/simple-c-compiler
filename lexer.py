FILE_PATH = "examples/valid/multi_digit.c"


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

def tokenize(file_path):
    flat = ""

    with open(file_path, 'r') as file:
        for line in file:
            flat += line
    
    in_digit = False
    in_quotes = False
    in_identifier = False

    tokens = []
    _token = ""

    for i in range(len(flat)):
        c = flat[i]
        if in_digit:
            if is_digit(c) or is_letter(c):
                _token += c # lexical errors will be treated later
            elif is_space(c):
                tokens.append(_token)
                _token = ""
                in_digit = False
            elif is_double_quotes(c):
                tokens.append(_token)
                _token = c
                in_digit = False
                in_quotes = True
            elif is_special(c):
                tokens.append(_token)
                _token = ""
                tokens.append(c)
                in_digit = False
            else:
                raise ValueError("Tokenizer (in-digit) got an unidentified character!")
        elif in_quotes:
            if is_double_quotes(c):
                _token += c
                tokens.append(_token)
                _token = ""
                in_quotes = False
            else:
                _token += c
        elif in_identifier:
            if is_digit(c) or is_letter(c) or is_underscore(c):
                _token += c
            elif is_space(c):
                tokens.append(_token)
                _token = ""
                in_identifier = False
            elif is_double_quotes(c):
                tokens.append(_token)
                _token = c
                in_identifier = False
                in_quotes = True
            elif is_special(c):
                tokens.append(_token)
                _token = ""
                tokens.append(c)
                in_identifier = False
            else:
                raise ValueError("Tokenizer (in-identifier) got an unidentified character!")
        else:
            if is_space(c):
                pass
            elif is_digit(c):
                in_digit = True
                _token += c
            elif is_double_quotes(c):
                in_quotes = True
                _token += c
            elif is_letter(c) or is_underscore(c):
                in_identifier = True
                _token += c
            elif is_special(c):
                tokens.append(c)
            else:
                raise ValueError("Tokenizer (first-digit) got an unidentified character!")

    if _token != "":
        tokens.append(_token)
    return tokens


if __name__ == '__main__':
    print(tokenize(FILE_PATH))
