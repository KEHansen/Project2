#include <stdio.h>
#include <string.h>

char testResult[1024] = "0011000000000000\n"
                        "0010100000000011\n"
                        "0010011000000001\n"
                        "0101011011100000\n"
                        "0000000000000000\n"
                        "0000000000000110\n"
                        "0000000001100001\n"
                        "0000000001100010\n"
                        "0000000001100011\n"
                        "0000000000000000\n";

char ourResult[1024] ="0011000000000000\n"
                      "0010100000000011\n"
                      "0010011000000001\n"
                      "0101011011100000\n"
                      "0000000000000000\n"
                      "0000000000000110\n"
                      "0000000001100001\n"
                      "0000000001100010\n"
                      "0000000001100011\n"
                      "0000000000000000\n";
int main() {

    if (strcmp(testResult, ourResult) == 0) {
        printf("They are identical!");
    } else {
        printf("They are NOT identical");
    }
    return 0;
}