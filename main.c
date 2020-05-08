#include <stdio.h>
#include <string.h>

// Defining all of the registers
#define R0 "000"
#define R1 "001"
#define R2 "010"
#define R3 "011"
#define R4 "100"
#define R5 "101"
#define R6 "110"
#define R7 "111"

// Defining the assembly instructions
#define ADD "0001"
#define LD "0010"
#define NOT "1001"
#define ST "0111"
#define LDR "0110"
#define BR "0000"

// Defining the offsets
#define NOTOFFSET "111111"
#define PCOFFSET6 "000000"
#define PCOFFSET9 "000000000"

char operator[8];
char transOpt[8];
char operand[3][8];
char transOpd[16];
char output[16];

int x;


void operatorTranslater(char opt[]) {
    if (strcmp(opt, "ADD") == 0) {
        sprintf(transOpt, "%s", ADD);
        x = 3;
        return;
    } else if (strcmp(opt, "LD") == 0) {
        sprintf(transOpt, "%s", LD);
        x = 2;
        return;
    } else if (strcmp(opt, "NOT") == 0) {
        sprintf(transOpt, "%s", NOT);
        x = 2;
        return;
    } else if (strcmp(opt, "ST") == 0) {
        sprintf(transOpt, "%s", ST);
        return;
    } else if (strcmp(opt, "LDR") == 0) {
        sprintf(transOpt, "%s", LDR);
        return;
    } else if (strcmp(opt, "BR") == 0) {
        sprintf(transOpt, "%s", BR);
        return;
    }
}

void operandTranslater(char opd[]) {
    if (strcmp(opd, "R0") == 0) {
        sprintf(transOpd, "%s", R0);
        return;
    }

}




int main(void) {
    int i;
    char input[16];
    printf("Input an LC3 assembly instruction:\n");
    gets(input);

    for (i = 0; i < strlen(input) ; ++i) {
        if (input[i] != ' ') {
            operator[i] = input[i];
        } else {
            break;
        }
    }

    operatorTranslater(operator);

    int j = i+1;
    i = 0;
    for (int k = 0; k < 1; ++k) {
        for (j = j; j < strlen(input); ++j) {
            if (input[j] != ' ') {
                operand[k][i] = input[j];
                i++;
            } else {
                j++;
                i = 0;
                break;
            }
        }
    }

    operandTranslater(operand[0]);

    strcpy(output, transOpt);
    strcat(output, transOpd);

    char str[80];
    strcpy(str, "these ");
    strcat(str, "strings ");
    strcat(str, "are ");
    strcat(str, "concatenated.");

    printf("%s", output);





}