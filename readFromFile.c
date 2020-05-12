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
#define AND "0101"
#define LD "0010"
#define LDR "0110"
#define LDI "1010"
#define LEA "1110"
#define NOT "1001"
#define ST "0011"
#define STR "0111"
#define STI "1011"
#define JSR "0100"
#define RET "1100000111000000"
#define BR "0000"

// Defining the offsets
#define NOTOFFSET "111111"
#define END "0000000000000000"

// Defining file paths
#define personalPath "C:/Users/kehan_000/" // Remember to change to personal path
#define readPath "ClionProjects/Project2/tmp/assemblycode.txt"
#define writePath "ClionProjects/Project2/tmp/machinecode.txt"

char buff[256];
char operator[8];
char operand[3][8];
char transOpt[4];
char transOpd[12];
char decimal[9];
char hex[5];
char output[17];
char Sblkw[8];
char stringz[64];
char stringzReady[64];
char labels[16][16];
int labelLine[16];

int numberOfOperands;
int offset;
int Nblkw;
int decimalNumber;
int currentLine = 0;
int numberOfLabels = 0;
int labelJump;

// Paths
char readFilePath[100];
char writeFilePath[100];

FILE *readFile;
FILE *writeFile;


void determineBR(char *opt);
void decimalToBinary(int n);
void hexToBinary(char *opd);
void BLKW();
void STRINGZ();
void setLabel();
int readLabel(char *opd);
int doesLabelExist();
void createLabels();
int searchForLabel();

// Translates the operator and determines the offset and the number of operands for the given operator
void operatorTranslater(char opt[]) {
    if (strcmp(opt, "ADD") == 0) {
        sprintf(transOpt, "%s", ADD);
        numberOfOperands = 3;
        offset = 5;
    } else if (strcmp(opt, "AND") == 0) {
        sprintf(transOpt, "%s", AND);
        numberOfOperands = 3;
        offset = 5;
    } else if (strcmp(opt, "LD") == 0) {
        sprintf(transOpt, "%s", LD);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "LDR") == 0) {
        sprintf(transOpt, "%s", LDR);
        numberOfOperands = 3;
        offset = 6;
    } else if (strcmp(opt,"LDI") == 0) {
        sprintf(transOpt, "%s", LDI);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt,"LEA") == 0) {
        sprintf(transOpt, "%s", LEA);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "NOT") == 0) {
        sprintf(transOpt, "%s", NOT);
        numberOfOperands = 2;
    } else if (strcmp(opt, "ST") == 0) {
        sprintf(transOpt, "%s", ST);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "STR") == 0) {
        sprintf(transOpt, "%s", STR);
        numberOfOperands = 3;
        offset = 6;
    } else if (strcmp(opt, "STI") == 0) {
        sprintf(transOpt, "%s", STI);
        numberOfOperands = 2;
        offset = 9;
    } else if (strcmp(opt, "JSR") == 0) {
        sprintf(transOpt, "%s", JSR);
        strcat(transOpt, "1");
        numberOfOperands = 1;
        offset = 11;
    } else if (strcmp(opt, "RET") == 0) {
        sprintf(transOpt, "%s", RET);
    } else if (opt[0] == 'B' && opt[1] == 'R') {
        sprintf(transOpt, "%s", BR);
        numberOfOperands = 1;
        offset = 9;
        determineBR(opt);

        /* The additional assembler directives that needs to be implemented in order to communicate with an LC3
            assembler file */
    } else if (strcmp(operator, ".ORIG") == 0) {
        numberOfOperands = 1;
    } else if (strcmp(operator, ".BLKW") == 0) {
        BLKW();
    } else if (strcmp(operator, ".FILL") == 0) {
        numberOfOperands = 1;
        offset = 16;
    } else if (strcmp(operator, ".STRINGZ") == 0) {
        offset = 16;
        STRINGZ();
    } else if (strcmp(operator, ".END") == 0) {
        return;
    } else {
        fscanf(readFile, "%s", operator);
        operatorTranslater(operator);
        return;
    }
    strcat(output, transOpt);
}

// Sets a label with the given name
void setLabel() {
    if (!(doesLabelExist())) {
        sprintf(labels[numberOfLabels], "%s", operator);
        labelLine[numberOfLabels] = currentLine;
        numberOfLabels++;
    }
}

// Check if a label exist within the program
int doesLabelExist() {
    for (int i = 0; i < strlen((const char *) labels); ++i) {
        if (strcmp(operator, labels[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void STRINGZ() {
    fgets(stringz, sizeof(stringz), readFile);
    int j = 0;
    int true = 0;
    for (int i = 0; i < strlen(stringz); ++i) {
        if (stringz[i] == '"') {
            true += 1;
        } else if (true % 2 == 1) {
            stringzReady[j] = stringz[i];
            j++;
        }
    }
    for (int i = 0; i < strlen(stringzReady); ++i) {
        decimalToBinary((int)stringzReady[i]);
        fprintf(writeFile, "%s\n", output);
        currentLine++;
        memset(output, '\0', sizeof(output));
    }
    sprintf(transOpt, "%s", END);
}

void determineBR(char *opt) {
    if (strcmp(opt,"BRnzp") == 0) {
        strcat(transOpt, "111");
    } else if (strcmp(opt,"BRnz") == 0) {
        strcat(transOpt, "110");
    } else if (strcmp(opt,"BRnp") == 0) {
        strcat(transOpt, "101");
    } else if (strcmp(opt,"BRzp") == 0) {
        strcat(transOpt, "011");
    } else if (strcmp(opt,"BRn") == 0) {
        strcat(transOpt, "100");
    } else if (strcmp(opt,"BRz") == 0) {
        strcat(transOpt, "010");
    } else if (strcmp(opt,"BRp") == 0) {
        strcat(transOpt, "001");
    } else if (strcmp(opt,"BR") == 0) {
        strcat(transOpt, "111");
    }
}

void BLKW() {
    fscanf(readFile, "%s", operand[0]);
    for (int i = 1; i < strlen(operand[0]); ++i) { // Removes the hashtag from the string
        Sblkw[i-1] = operand[0][i];
    }
    sscanf(Sblkw, "%d", &Nblkw);
    sprintf(transOpt, "%s", END);
    strcpy(output, transOpt);
    for (int i = 0; i < Nblkw - 1; ++i) {
        fprintf(writeFile, "%s\n", output);
    }
}

// Translates the operands
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
        for (int i = 1; i < strlen(opd); ++i) { // Removes the hashtag from the string
            decimal[i-1] = opd[i];
        }
        sscanf(decimal, "%d", &decimalNumber); // Converts the string to an integer
        decimalToBinary(decimalNumber);
    } else if (opd[0] == 'x') {
        hexToBinary(opd);
    } else {
        labelJump = readLabel(opd);
        decimalToBinary(labelJump);
    }
    strcat(output, transOpd);
}

// Converts decimal number into binary in the length of the given offset
void decimalToBinary(int n) {
    int c, k;

    for (c = offset - 1; c >= 0; c--)
    {
        k = n >> c;

        if (k & 1)
            strcat(output, "1");
        else
            strcat(output, "0");
    }
}

// Converts hex to binary
void hexToBinary(char *opd) {

    for (int i = 1; i < strlen(opd); ++i) { // Removes the x from the .Orig
        hex[i-1] = opd[i];
    }

    for (int i = 0; strlen(hex) != sizeof(hex) - 1; ++i) {  // Makes sure that the .Orig is always 4 digits long.
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
                strcat(transOpd, "0000");
                break;
            case '1':
                strcat(transOpd, "0001");
                break;
            case '2':
                strcat(transOpd, "0010");
                break;
            case '3':
                strcat(transOpd, "0011");
                break;
            case '4':
                strcat(transOpd, "0100");
                break;
            case '5':
                strcat(transOpd, "0101");
                break;
            case '6':
                strcat(transOpd, "0110");
                break;
            case '7':
                strcat(transOpd, "0111");
                break;
            case '8':
                strcat(transOpd, "1000");
                break;
            case '9':
                strcat(transOpd, "1001");
                break;
            case 'a':
            case 'A':
                strcat(transOpd, "1010");
                break;
            case 'b':
            case 'B':
                strcat(transOpd, "1011");
                break;
            case 'c':
            case 'C':
                strcat(transOpd, "1100");
                break;
            case 'd':
            case 'D':
                strcat(transOpd, "1101");
                break;
            case 'e':
            case 'E':
                strcat(transOpd, "1110");
                break;
            case 'f':
            case 'F':
                strcat(transOpd, "1111");
                break;
        }
    }
}

// Reads the label and calculates the corresponding number.
int readLabel(char *opd) {
    int l = 0;
    for (int i = 0; i < strlen((const char *) labels); ++i) {
        if (strcmp(opd,labels[i]) == 0) {
            l = labelLine[i];
            break;
        }
    }
    if (l != 0) {
        return l - (currentLine + 1);
    }
    return 0;
}

// Checks for immediate or register version of ADD or AND
void checkADD_AND(int i) {
    if ((strcmp(operator, "ADD") == 0 || strcmp(operator, "AND") == 0) && i == 2) {
        if (operand[i][0] == 'R') {
            strcat(output, "000");
        } else if (operand[i][0] == '#') {
            strcat(output, "1");
        }
    }
}

// Clears all of the character arrays (strings) and resets integer values to zero
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
    memset(buff, '\0', sizeof(buff));
    numberOfOperands = 0;
    offset = 0;
}

// Opens the two files
void openFiles() {
    strcpy(readFilePath, personalPath);
    strcat(readFilePath, readPath);
    readFile = fopen(readFilePath, "r");

    strcpy(writeFilePath, personalPath);
    strcat(writeFilePath, writePath);
    writeFile = fopen(writeFilePath, "w");
}

// Closes the two files
void closeFiles() {
    fclose(readFile);
    fclose(writeFile);
}

void createLabels() {
    openFiles();
    while (1) {
        clear();
        fscanf(readFile, "%s", operator);
        if (strcmp(operator, "") == 0) { // Has reached the end of the program
            closeFiles();
            currentLine = 0;
            return;
        }
        if (searchForLabel()) {
            currentLine++;
        }
    }
}

int searchForLabel() {
    if (strcmp(operator, ".ORIG") == 0 || strcmp(operator, ".FILL") == 0 || strcmp(operator, ".BLKW") == 0 || strcmp(operator, ".STRINGZ") == 0) {
        fgets(buff, sizeof(buff), readFile);
    } else if (strcmp(operator, "ADD") == 0 || strcmp(operator, "AND") == 0 || strcmp(operator, "NOT") == 0) {
        fgets(buff, sizeof(buff), readFile);
    } else if (strcmp(operator, "LD") == 0 || strcmp(operator, "LDI") == 0 || strcmp(operator, "LDR") == 0 || strcmp(operator, "LEA") == 0) {
        fgets(buff, sizeof(buff), readFile);
    } else if (strcmp(operator, "ST") == 0 || strcmp(operator, "STI") == 0 || strcmp(operator, "STR") == 0) {
        fgets(buff, sizeof(buff), readFile);
    } else if (strcmp(operator, "JSR") == 0 || strcmp(operator, "RET") == 0 || (operator[0] == 'B' && operator[1] == 'R')) {
        fgets(buff, sizeof(buff), readFile);
    } else if (strcmp(operator, ".END") == 0) {
        return 0;
    } else {
        setLabel();
        return 0;
    }
    return 1;
}

int main(void) {

    createLabels();
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
            checkADD_AND(i);
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
        currentLine++;
    }
}