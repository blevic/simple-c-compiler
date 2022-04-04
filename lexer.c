#include <stdio.h>

int main(void)
{
    FILE *file;
    int i = 0;

    file = fopen("examples/return_3.c", "r");

    while (1) {
        i = fgetc(file);
 
        if (feof(file))
            break;
 
        printf("%c", i);
    }

    fclose(file);
    return 0;
}
