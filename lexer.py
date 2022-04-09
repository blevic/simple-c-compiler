FILE_PATH = "examples/valid/return_3.c"


def is_space_char(c):
    return c.isspace()


def is_special_char(c):
    return c in ['(', ')', '{', '}', '[', ']', ',', ';', '+', '-']


def is_digit(c):
    return c.isdigit()


def is_letter(c):
    return c.isalpha()


def tokenize(file_path):
    tokens = []
    flat = ""
    with open(file_path, 'r') as file:
        for line in file:
            flat += line
    
    in_digit = False
    in_quotes = False
    in_identifier = False
    constructing_token = ""
    for i in range(len(flat)):
        c = flat[i]
        if in_digit:
            pass
        elif in_quotes:
            pass
        elif in_identifier:
            pass
        else:
            if is_space_char(c):
                pass
            elif is_digit(c):
                in_digit = True
                constructing_token += c
            elif c == '"':
                in_quotes = True
                constructing_token += c
            elif is_letter(c):
                in_identifier = True
                constructing_token += c
            elif is_special_char(c):
                tokens.append(c)

    return tokens


if __name__ == '__main__':
    print(tokenize(FILE_PATH))
