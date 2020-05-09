#include <stdio.h>
#include <string.h>

int main() {
    char str[20];

    strcpy(str, "a");
    strcat(str, "b");
    strcat(str, "c");
    strcat(str, "d");
    //printf("%s", str);
    //printf("\n");

    str[0] = '\0';
    strcpy(str, "x");
    strcat(str, "y");
    strcat(str, "z");
    printf("%s", str);

    return 0;
}