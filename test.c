#include <stdio.h>
#include <string.h>



int main() {

    FILE *wFile;
    wFile = fopen("/Users/kehan_000/ClionProjects/Project/tmp/assemblycode.txt", "w+");
    fprintf(wFile, "Test 1 2 3\n");
    fputs("3 2 1 tseT\n", wFile);
    fclose(wFile);


    return 1;
}