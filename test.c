#include <stdio.h>
#include <string.h>

#define personalPath "C:/Users/kehan_000/"
#define readPath "ClionProjects/Project2/tmp/assemblycode.txt"
#define writePath "ClionProjects/Project2/tmp/machinecode.txt"

char rfp[100];
char wfp[100];
char input[16];

FILE *rf;
FILE *wf;


void openFiles() {
    strcpy(rfp, personalPath);
    strcat(rfp, readPath);
    rf = fopen(rfp, "r");

    strcpy(wfp, personalPath);
    strcat(wfp, writePath);
    wf = fopen(wfp, "w");
}

void closeFiles() {
    fclose(rf);
    fclose(wf);
}

int main() {

    openFiles();


    fscanf(rf, "%s", input);

    if (strcmp(input, "") == 0) {
        printf("det virker");
    } else {
        printf("det virker ikke");
    }


    closeFiles();

    return 0;
}