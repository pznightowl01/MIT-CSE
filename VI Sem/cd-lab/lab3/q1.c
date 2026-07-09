// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

// Write functions to identify the following tokens. 
//a.Arithmetic, relational and logical operators. 
//b.Special symbols, keywords, numerical constants, string literals and identifiers.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int row = 1, col = 0;
int lastPrintedRow = 1;

struct token {
    char token_name[20];
    int index;
    unsigned int row;
    unsigned int col;
    char type[20];
};

char *keywords[] = {"char","float","if","else","while","for","return"};

int isKeyword(char *str) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void getNextToken(char *name, int r, int c) {
    struct token t;
    strcpy(t.token_name, name);
    t.row = r;
    t.col = c;

    if (r != lastPrintedRow) {
        printf("\n");
        lastPrintedRow = r;
    }
    printf("<%s,%d,%d>", t.token_name, t.row, t.col);
}

int main() {
    FILE *fptr;
    char filename[50], ch, buf[50];
    int i;

    printf("Name : Princita Zina Miranda");
    printf("\nSection : SCE-C");
    printf("\nReg No. : 220905115 (Roll No. 17)\n");
    printf("\n");

    fptr = fopen("q1in.c", "r");
    if (fptr == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        col++;

        if (ch == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (isspace(ch))
            continue;

        if (isalpha(ch) || ch == '_') {
            int startCol = col;
            i = 0;
            buf[i++] = ch;

            while (isalnum(ch = fgetc(fptr)) || ch == '_') {
                buf[i++] = ch;
                col++;
            }
            buf[i] = '\0';
            ungetc(ch, fptr);

            if (isKeyword(buf))
                getNextToken(buf, row, startCol);
            else
                getNextToken("id", row, startCol);
        }

        else if (isdigit(ch)) {
            int startCol = col;
            i = 0;
            buf[i++] = ch;

            while (isdigit(ch = fgetc(fptr))) {
                buf[i++] = ch;
                col++;
            }
            buf[i] = '\0';
            ungetc(ch, fptr);

            getNextToken("num", row, startCol);
        }

        else if (ch == '"') {
            int startCol = col;
            while ((ch = fgetc(fptr)) != '"' && ch != EOF)
                col++;
            getNextToken("string", row, startCol);
        }

        else if (strchr("+-*/%=<>!&|", ch)) {
            char op[3];
            int startCol = col;
            op[0] = ch;
            op[1] = fgetc(fptr);

            if ((op[0] == '&' && op[1] == '&') ||
                (op[0] == '|' && op[1] == '|') ||
                (op[1] == '=')) {
                op[2] = '\0';
                col++;
            } else {
                ungetc(op[1], fptr);
                op[1] = '\0';
            }
            getNextToken(op, row, startCol);
        }

        else if (strchr("(){}[],;", ch)) {
            char sym[2] = {ch, '\0'};
            getNextToken(sym, row, col);
        }
    }

    fclose(fptr);
    return 0;
}
