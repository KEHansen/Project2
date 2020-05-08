#include <stdio.h>
#include <string.h>

#define R0 "000"
#define R1 "001"
#define R2 "010"
#define R3 "011"
#define R4 "100"
#define R5 "101"
#define R6 "110"
#define R7 "111"
#define ADD "0001"
#define LD "0010"
#define NOT "1001"
#define ST "0111"
#define LDR "0110"
#define BR "0000"
#define NOTOFFSET "111111"
#define PCOFFSET6 "000000"
#define PCOFFSET9 "000000000"

char ans[3] = "000";
char opAns[] = "";
char command[16][16];
char DR[2], DRConverted[3];
char SR[2], SRConverted[3];
char SR1[3], SR1Converted[3];
char SR2[2], SR2Converted[3];
char Fill[];
char output[16];

const char* RegisterTransformer(char R[]) {
    if (strcmp(R, "R0") == 0) {
        sprintf(ans, "%s", R0);
    } else if (strcmp(R, "R1") == 0) {
        sprintf(ans, "%s", R1);
    } else if (strcmp(R, "R2") == 0) {
        sprintf(ans, "%s", R2);
    } else if (strcmp(R, "R3") == 0) {
        sprintf(ans, "%s", R3);
    } else if (strcmp(R, "R4") == 0) {
        sprintf(ans, "%s", R4);
    } else if (strcmp(R, "R5") == 0) {
        sprintf(ans, "%s", R5);
    } else if (strcmp(R, "R6") == 0) {
        sprintf(ans, "%s", R6);
    } else if (strcmp(R, "R7") == 0) {
        sprintf(ans, "%s", R7);
    }

    return ans;
}

const char* OperationTerminator(char Op[]) {
// Check which operation

    if (strcmp(Op, "ADD") == 0) {
        sprintf(opAns, "%s", ADD);
        DR[0] = command[1][0];
        DR[1] = command[1][1];
        SR1[0] = command[2][0];
        SR1[1] = command[2][1];
        Fill[0] = command[3][0];
        Fill[1] = command[3][1];
        Fill[2] = command[3][2];
        SR2[0] = command[4][0];
        SR2[0] = command[4][1];
        sprintf(DRConverted, "%s", RegisterTransformer(DR));
        sprintf(SR1Converted, "%s", RegisterTransformer(SR1));
        sprintf(SR2Converted, "%s", RegisterTransformer(SR2));

        // ADD DR SR1 FILL SR2
        sprintf(opAns, "%s%s%s%s%s", ADD, DRConverted, SR1Converted, Fill, SR2Converted);
    } else if (strcmp(Op, "LD") == 0) {
        DR[0] = command[1][0];
        DR[1] = command[1][1];
        DR[1] = command[1][2];
        sprintf(DRConverted, "%s", RegisterTransformer(DR));
        // LD DR PCOFFSET9
        //todo Mangler at sætte værdien ind i offsettet. f.eks: -3 1111111111111101 2's complement
        sprintf(opAns, "%s%s%s", LD, DR, PCOFFSET9);

    } else if (strcmp(Op, "NOT") == 0) {
        DR[0] = command[1][0];
        DR[1] = command[1][1];
        SR[0] = command[2][0];
        SR[1] = command[2][1];
        sprintf(DRConverted, "%s", RegisterTransformer(DR));
        sprintf(SRConverted, "%s", RegisterTransformer(SR));

        // NOT DR SR NOTOFFSET
        sprintf(opAns, "%s%s%s%s", NOT, DRConverted, SRConverted, NOTOFFSET);

    } else if (strcmp(Op, "ST") == 0) {
        sprintf(opAns, "%s", ST);
        SR[0] = command[1][0];
        SR[1] = command[1][1];
        sprintf(SRConverted, "%s", RegisterTransformer(DR));

    } else if (strcmp(Op, "LDR") == 0) {
        DR[0] = command[1][0];
        DR[1] = command[1][1];
        sprintf(DRConverted, "%s", RegisterTransformer(DR));

        //todo baseR
        char baseR = "baseR";
        // LDR DR BASER PCOFFSET6
        sprintf(opAns, "%s%s%s%s", LDR, DR, baseR, PCOFFSET6);

    } else if (strcmp(Op, "BR") == 0) {
        char n = 0;
        char z = 0;
        char p = 0;
        // n z p
        if (command[1][0] == 'n' || command[1][0] == 'z' || command[1][0] == 'p') {
            if (command[1][0] != 'n' && command[1][0] != 'z') {
                p = 1;
            } else if (command[1][0] != 'p' && command[1][0] != 'z') {
                n = 1;
            } else if (command[1][0] != 'n' && command[1][0] != 'p') {
                z = 1;
            }

        } else if (command[2][0] == 'n' || command[2][0] == 'z' || command[2][0] == 'p') {
            if (command[2][0] != 'n' && command[2][0] != 'z') {
                p = 1;
            } else if (command[2][0] != 'p' && command[2][0] != 'z') {
                n = 1;
            } else if (command[2][0] != 'n' && command[2][0] != 'p') {
                z = 1;
            }

        } else if (command[3][0] == 'n' || command[3][0] == 'z' || command[3][0] == 'p') {
            if (command[3][0] != 'n' && command[3][0] != 'z') {
                p = 1;
            } else if (command[3][0] != 'p' && command[3][0] != 'z') {
                n = 1;
            } else if (command[3][0] != 'n' && command[3][0] != 'p') {
                z = 1;
            }
        }

        // BR n z p PCOFFSET9
        //TODO: Skal måske lige gentænke denne så formattet bliver BRnzp i stedet for BR n z p. Hvis der er tid!
        sprintf(opAns, "%s%c%c%c%s", BR, n, z, p, PCOFFSET9) ;
        return opAns;
    }
    return opAns;
}

int main(void) {
    // VARIABLES
    int i, j, counter;
    char Op[4];
    char input[16];

    // Input
    printf("Input an LC3 assembly instruction:\n");
    gets(input);

    // Split input into OP and rest
    j=0; counter=0;
    for(i = 0; i <= (strlen(input)); i++) {
        // If we find a space or end of line
        if(input[i] == ' ' || input == '\0') {
            command[counter][j] = '\0';
            counter++;      // Find next word
            j=0;            // Init index to 0
        } else {
            // If we find a character
            command[counter][j] = input[i];
            j++;
        }
    }
    // OP
    Op[0] = command[0][0];
    Op[1] = command[0][1];
    Op[2] = command[0][2];
    Op[3] = command[0][3];

    OperationTerminator(Op);

    printf("The corresponding machine instruction is:\n");
    printf("%s", output);
}


/*
    // Get String of Register
    char Register[2];
    printf("Enter a Register: \n");
    gets(Register);
    printf(RegisterTransformer(Register));
 */