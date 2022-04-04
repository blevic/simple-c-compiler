#include <stdio.h>

static const char FILE_PATH[] = "examples/return_3.c";

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
