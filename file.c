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
#define OFFSET6 "000000"
#define PCOFFSET9 "000000000"

// Defining file paths
#define personalPath "C:/Users/kehan_000/" // Remember to change to personal path
#define readPath "ClionProjects/Project2/tmp/assemblycode.txt"
#define writePath "ClionProjects/Project2/tmp/machinecode.txt"

char operator[8];
char operand[3][8];
char transOpt[4];
char transOpd[12];
char decimal[9];
char hex[5];
char output[17];

int numberOfOperands;
int offset;

char readFilePath[100];
char writeFilePath[100];

FILE *readFile;
FILE *writeFile;


void determineBR(char *opt);

void decimalToBinary(char *opd);

void hexToBinary(char *opd);

// Translates the operator and determines the offset and the number of operands for the given operator
void operatorTranslater(char opt[]) {
    if (strcmp(opt, "ADD") == 0) {
        sprintf(transOpt, "%s", ADD);
        numberOfOperands = 3;
        offset = 5;
    } else if (strcmp(opt, "LD") == 0) {
        sprintf(transOpt, "%s", LD);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "NOT") == 0) {
        sprintf(transOpt, "%s", NOT);
        numberOfOperands = 2;
    } else if (strcmp(opt, "ST") == 0) {
        sprintf(transOpt, "%s", ST);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "LDR") == 0) {
        sprintf(transOpt, "%s", LDR);
        numberOfOperands = 3;
        offset = 6;
    } else if (opt[0] == 'B' && opt[1] == 'R') {
        sprintf(transOpt, "%s", BR);
        strcpy(output, transOpt);
        determineBR(opt);
        sprintf(transOpt, "%s", PCOFFSET9);
        strcat(output, transOpt);
        return;
    } else if (strcmp(operator, ".ORIG") == 0) {
        numberOfOperands = 1;
    } else if (strcmp(operator, ".BLKW") == 0) {

    } else if (strcmp(operator, ".FILL") == 0) {

    } else if (strcmp(operator, ".STRINGZ") == 0) {

    } else if (strcmp(operator, ".END") == 0) {

    }
    strcpy(output, transOpt);
}



void determineBR(char *opt) {
    if (strcmp(opt,"BRnzp") == 0) {
        strcat(output, "111");
    } else if (strcmp(opt,"BRnz") == 0) {
        strcat(output, "110");
    } else if (strcmp(opt,"BRnp") == 0) {
        strcat(output, "101");
    } else if (strcmp(opt,"BRzp") == 0) {
        strcat(output, "011");
    } else if (strcmp(opt,"BRn") == 0) {
        strcat(output, "100");
    } else if (strcmp(opt,"BRz") == 0) {
        strcat(output, "010");
    } else if (strcmp(opt,"BRp") == 0) {
        strcat(output, "001");
    } else if (strcmp(opt,"BR") == 0) {
        strcat(output, "000");
    }
}

// Translates the operands to
void operandTranslater(char opd[]) {
    if (strcmp(opd, "R0") == 0) {
        sprintf(transOpd, "%s", R0);
    } else if (strcmp(opd, "R1") == 0) {
        sprintf(transOpd, "%s", R1);
    } else if (strcmp(opd, "R2") == 0) {
        sprintf(transOpd, "%s", R2);
    } else if (strcmp(opd, "R3") == 0) {
        sprintf(transOpd, "%s", R3);
    } else if (strcmp(opd, "R4") == 0) {
        sprintf(transOpd, "%s", R4);
    } else if (strcmp(opd, "R5") == 0) {
        sprintf(transOpd, "%s", R5);
    } else if (strcmp(opd, "R6") == 0) {
        sprintf(transOpd, "%s", R6);
    } else if (strcmp(opd, "R7") == 0) {
        sprintf(transOpd, "%s", R7);
    } else if (opd[0] == '#'){
        decimalToBinary(opd);
        return;
    } else if (opd[0] == 'x') {
        hexToBinary(opd);
        return;
    }
    strcat(output, transOpd);
}

// Converts decimal number into binary in the length of the given offset
void decimalToBinary(char *opd) {
    int n, c, k;
    for (int i = 1; i < strlen(opd); ++i) { // Removes the hashtag from the string
        decimal[i-1] = opd[i];
    }
    sscanf(decimal, "%d", &n); // Converts the string to an integer
    for (c = offset - 1; c >= 0; c--)
    {
        k = n >> c;

        if (k & 1)
            strcat(output, "1");
        else
            strcat(output, "0");
    }
}

void hexToBinary(char *opd) {

    for (int i = 1; i < strlen(opd); ++i) { // Removes the hashtag from the string
        hex[i-1] = opd[i];
    }

    for (int i = 0; strlen(hex) != sizeof(hex) - 1; ++i) {
        hex[3] = hex[2];
        hex[2] = hex[1];
        hex[1] = hex[0];
        hex[0] = '0';
    }

    for (int i = 0; i < strlen(hex); i++)
    {
        switch(hex[i])
        {
            case '0':
                strcat(output, "0000");
                break;
            case '1':
                strcat(output, "0001");
                break;
            case '2':
                strcat(output, "0010");
                break;
            case '3':
                strcat(output, "0011");
                break;
            case '4':
                strcat(output, "0100");
                break;
            case '5':
                strcat(output, "0101");
                break;
            case '6':
                strcat(output, "0110");
                break;
            case '7':
                strcat(output, "0111");
                break;
            case '8':
                strcat(output, "1000");
                break;
            case '9':
                strcat(output, "1001");
                break;
            case 'a':
            case 'A':
                strcat(output, "1010");
                break;
            case 'b':
            case 'B':
                strcat(output, "1011");
                break;
            case 'c':
            case 'C':
                strcat(output, "1100");
                break;
            case 'd':
            case 'D':
                strcat(output, "1101");
                break;
            case 'e':
            case 'E':
                strcat(output, "1110");
                break;
            case 'f':
            case 'F':
                strcat(output, "1111");
                break;
        }
    }
}

// Checks for immediate or register version of add
void checkADD(int i) {
    if (strcmp(operator, "ADD") == 0 && i == 2) {
        if (operand[i][0] == 'R') {
            strcat(output, "000");
        } else if (operand[i][0] == '#') {
            strcat(output, "1");
        }
    }
}

// Clears all of the character arrays (strings)
void clear() {
    memset(operator, '\0', sizeof(operator));
    memset(operand[0], '\0', sizeof(operand[0]));
    memset(operand[1], '\0', sizeof(operand[1]));
    memset(operand[2], '\0', sizeof(operand[2]));
    memset(transOpt, '\0', sizeof(transOpt));
    memset(transOpd, '\0', sizeof(transOpd));
    memset(decimal, '\0', sizeof(decimal));
    memset(hex, '\0', sizeof(hex));
    memset(output, '\0', sizeof(output));
}

void openFiles() {
    strcpy(readFilePath, personalPath);
    strcat(readFilePath, readPath);
    readFile = fopen(readFilePath, "r");

    strcpy(writeFilePath, personalPath);
    strcat(writeFilePath, writePath);
    writeFile = fopen(writeFilePath, "w");
}

void closeFiles() {
    fclose(readFile);
    fclose(writeFile);
}

int main(void) {

    openFiles();

    while (1) {

        clear();

        fscanf(readFile, "%s", operator);

        if (strcmp(operator, "") == 0) { // Stops the program if 'true'
            closeFiles();
            return 0;
        }

        operatorTranslater(operator);

        // Storing Operands in array / matrix
        for (int i = 0; i < numberOfOperands; ++i) {
            fscanf(readFile, "%s", operand[i]);
        }

        // Loop to translate the operands
        for (int i = 0; i < numberOfOperands; ++i) {
            checkADD(i);
            operandTranslater(operand[i]);
        }

        // Add NOTOFFSET if the operator is 'NOT'
        if (strcmp(operator, "NOT") == 0) {
            sprintf(transOpd, "%s", NOTOFFSET);
            strcat(output, transOpd);
        }

        // Makes sure nothing extra gets printed
        output[16] = '\0';

        // Prints the final machine code
        fprintf(writeFile, "%s\n", output);
    }
}