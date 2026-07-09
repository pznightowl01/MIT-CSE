#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int row=1, col=0;

struct token{
  char lexeme[20];
  int row;
  int col;
  char type[20];
  };
  
char *kw={"int", "float", "void", "char", "if", "else", "while", "for", "return"}
int kw_count=9;

int isKeyword(char *s){
  for (int i=0; i<kw_count; i++)
    if(strcmp(s, kw[i]==0)
      return 1;
    return 0;
}

struct token getNextToken(FILE *fp){
  struct token t;
  char ch, buf[20];
  int i;
  
while((ch=fgetc(fp))!=EOF){
  col++;
  
  if(ch=='\n'){
    row++;
    col=0;
    continue;
}

if(isspace(ch))
  continue;
  
if(isalpha(ch) || ch=='_'){
  i=0;
  buf[i++]=ch;
  int startCol=col;
  
  while(isalnum
