#include <stdio.h>

static const char FILE_PATH[] = "examples/return_3.c";

int main(void)
{
    FILE *file;
    int i = 0;

    file = fopen(FILE_PATH, "r");

    while (1) {
        i = fgetc(file);
 
        if (feof(file))
            break;
 
        printf("%c", i);
    }

    fclose(file);
    return 0;
}
