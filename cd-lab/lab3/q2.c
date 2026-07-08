// Name : Princita Zina Miranda
// Section : SCE-C
// Reg No. : 220905115 (Roll No. 17)

//Design a lexical analyzer that includes a getNextToken() function for processing a simple C program.The analyzer should construct a token structure containing the row number, column number, and token type for each identified token. The getNextToken() function must ignore tokens located within singleline or multi-line comments, as well as those found inside string literals. Additionally, it should strip out preprocessor directives.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int row = 1, col = 0;
int lastPrintedRow = 1;
struct token {
  char t_name[20];
  unsigned int row;
  unsigned int col;
};

char *kw[] = {"struct","float","char","if","else","while","for","return"};
int isKeyword(char *str) {
  for (int i = 0; i < 8; i++)
    if (strcmp(str, kw[i]) == 0)
      return 1;
return 0;
}
void getNextToken(char *lexeme, int r, int c) {
struct token t;
strcpy(t.t_name, lexeme);
t.row = r;
t.col = c;
if (r != lastPrintedRow) {
printf("\n");
lastPrintedRow = r;
}
printf("<%s,%d,%d>", t.t_name, t.row, t.col);
}
int main() {
FILE *fptr;
char filename[50], ch, buf[50];
int i;
printf("\nName : Princita Zina Miranda\nSection : SCE-C\nReg No. : 220905115 (Roll No.
17)\n");
printf("\n");
fptr = fopen("q1in.c", "r");
if (!fptr) {
printf("Cannot open file %s\n", filename);
exit(0);
}
while ((ch = fgetc(fptr)) != EOF) {
col++;
if (ch == '\n') {
row++;Name : Princita Zina Miranda, Section : SCE-C, Reg no. 220905115 (roll no. 17)
col = 0;
continue;
}
if (isspace(ch))
continue;
if (ch == '#') {
while ((ch = fgetc(fptr)) != '\n' && ch != EOF);
row++;
col = 0;
continue;
}
if (ch == '/') {
char next = fgetc(fptr);
if (next == '/') {
while ((ch = fgetc(fptr)) != '\n' && ch != EOF);
row++;
col = 0;
continue;
}
else if (next == '*') {
while ((ch = fgetc(fptr)) != EOF) {
if (ch == '\n') { row++; col = 0; }
if (ch == '*' && (ch = fgetc(fptr)) == '/')
break;
}
continue;
} else {
ungetc(next, fptr);
}
}
if (ch == '"') {
while ((ch = fgetc(fptr)) != '"' && ch != EOF) {
if (ch == '\n') { row++; col = 0; }
}
continue;
}
if (isalpha(ch) || ch == '_') {
int startCol = col;
i = 0;
buf[i++] = ch;
while (isalnum(ch = fgetc(fptr)) || ch == '_') {
buf[i++] = ch;
col++;
}Name : Princita Zina Miranda, Section : SCE-C, Reg no. 220905115 (roll no. 17)
buf[i] = '\0';
ungetc(ch, fptr);
if (isKeyword(buf))
getNextToken(buf, row, startCol);
else
getNextToken("id", row, startCol);
continue;
}
if (isdigit(ch)) {
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
continue;
}
if (strchr("+-*/%=<>!&|", ch)) {
int startCol = col;
char op[3];
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
continue;
}
if (strchr("(){}[],;", ch)) {
char sym[2] = {ch, '\0'};
getNextToken(sym, row, col);
continue;
}
}Name : Princita Zina Miranda, Section : SCE-C, Reg no. 220905115 (roll no. 17)
fclose(fptr);
return 0;
}
