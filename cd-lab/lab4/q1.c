#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

typedef struct Symbol {
    char lexeme[30];
    char datatype[20];
    int ptr;
    struct Symbol *next;
} Symbol;

Symbol *ST[TABLE_SIZE] = {NULL};
char lastType[20] = "";
int slno = 1;

int hash(char *str) {
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum += str[i];
    return sum % TABLE_SIZE;
}

int searchST(char *lexeme) {
    int index = hash(lexeme);
    Symbol *temp = ST[index];
    while (temp) {
        if (strcmp(temp->lexeme, lexeme) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void insertST(char *lexeme, char *datatype) {
    if (searchST(lexeme)) return;
    if (strcmp(lexeme, "main") == 0) return;

    int index = hash(lexeme);
    Symbol *node = (Symbol *)malloc(sizeof(Symbol));

    strcpy(node->lexeme, lexeme);
    strcpy(node->datatype, datatype);
    node->ptr = index;
    node->next = ST[index];
    ST[index] = node;
}

int row = 1, col = 0;
int lastPrintedRow = 1;

char *keywords[] = {"int","float","char","double","void", "if","else","for","while","return"
};
int kwCount = 10;

int isKeyword(char *str) {
    for (int i = 0; i < kwCount; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    return 0;
}

int isDataType(char *str) {
    return (!strcmp(str,"int") || !strcmp(str,"float") ||
            !strcmp(str,"char") || !strcmp(str,"double") ||
            !strcmp(str,"void"));
}

void printToken(char *token, int r, int c) {
    if (r != lastPrintedRow) {
        printf("\n");
        lastPrintedRow = r;
    }
    printf("<%s,%d,%d> ", token, r, c);
}

void lexicalAnalyze(FILE *fp) {
    char ch, buf[100];
    int i;

    while ((ch = fgetc(fp)) != EOF) {

        if (ch == '\n') {
            row++; col = 0;
            strcpy(lastType, "");
            continue;
        }

        col++;

        if (ch == ' ' || ch == '\t') continue;

        if (ch == '#') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            row++; col = 0;
            continue;
        }

        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                row++; col = 0;
                continue;
            }
            if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '\n') { row++; col = 0; }
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                continue;
            }
            ungetc(next, fp);
        }

        if (isalpha(ch) || ch == '_') {
            int startCol = col;
            i = 0;
            buf[i++] = ch;

            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buf[i++] = ch;
                col++;
            }
            buf[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(buf)) {
                printToken(buf, row, startCol);
                if (isDataType(buf))
                    strcpy(lastType, buf);
            } else {
                printToken("id", row, startCol);
                if (strlen(lastType) > 0)
                    insertST(buf, lastType);
            }
            continue;
        }

        if (isdigit(ch)) {
            int startCol = col;
            int hasDot = 0;

            while (1) {
                ch = fgetc(fp);
                if (isdigit(ch)) col++;
                else if (ch == '.' && !hasDot) {
                    hasDot = 1; col++;
                }
                else break;
            }
            ungetc(ch, fp);
            printToken("num", row, startCol);
            continue;
        }

        if (ch == '"') {
            int startCol = col;
            int closed = 0;

            while ((ch = fgetc(fp)) != EOF) {
                col++;
                if (ch == '"') { closed = 1; break; }
                if (ch == '\n') { row++; col = 0; }
            }

            if (closed)
                printToken("string literal", row, startCol);
            else
                printf("\nError: Unterminated string literal at %d,%d\n",
                       row, startCol);
            continue;
        }

        if (strchr("+-*/%=<>!&|", ch)) {
            char op[3] = {ch, '\0'};
            int startCol = col;

            char next = fgetc(fp);
            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|')) {
                op[1] = next;
                op[2] = '\0';
                col++;
            } else {
                ungetc(next, fp);
            }
            printToken(op, row, startCol);
            continue;
        }

        if (strchr("(){}[],;", ch)) {
            char sym[2] = {ch, '\0'};
            printToken(sym, row, col);
        }
    }
}

void displayST() {
    printf("\n\n---------------------------------------------\n");
    printf("SlNo  Lexeme      DataType    Ptr\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *temp = ST[i];
        while (temp) {
            printf("%-5d %-11s %-11s %d\n",
                   slno++, temp->lexeme, temp->datatype, temp->ptr);
            temp = temp->next;
        }
    }
    printf("---------------------------------------------\n");
}

int main() {
    FILE *fp = fopen("q2in.c", "r");
    if (!fp) {
        printf("File not found\n");
        return 0;
    }

    lexicalAnalyze(fp);
    fclose(fp);
    displayST();
    return 0;
}
