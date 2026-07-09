// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//1. Using getNextToken( ) implemented in Lab No 3, design a Lexical Analyser to implement the following symbol tables.
//a. local symbol table
//b. global symbol table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABSZ 50

struct token {
    char tk_name[20];
    unsigned int row, col;
    char type[20];
};

struct sym_ent {
    char lexe[20];
    char sym_type[10];
    char dt_type[10];
    int size;
    int h_val;
    char scope[20];
    struct sym_ent *next;
};

struct sym_ent *ST[TABSZ];
int line_no = 1, col_no = 0;

char *kw[] = {"int","float","char","void","if","else","while","for","return","bool"};
int kw_count = 10;

int isKeyword(char *s) {
    for(int i=0;i<kw_count;i++)
        if(strcmp(s, kw[i]) == 0) return 1;
    return 0;
}

int dt_size(char *t) {
    if(strcmp(t,"int")==0) return 4;
    if(strcmp(t,"float")==0) return 4;
    if(strcmp(t,"char")==0) return 1;
    if(strcmp(t,"bool")==0) return 1;
    return 0;
}

int hash(char *s) {
    int h=0;
    for(int i=0;s[i];i++)
        h = (h*31 + s[i]) % TABSZ;
    return h;
}

int searchST(char *lex) {
    int h = hash(lex);
    struct sym_ent *p = ST[h];
    while(p) {
        if(strcmp(p->lexe, lex) == 0)
            return p->h_val;
        p = p->next;
    }
    return -1;
}

void insertST(char *lex, char *stype, char *dtype, char *scope) {
    if(searchST(lex) != -1) return;

    int h = hash(lex);
    struct sym_ent *e = malloc(sizeof(struct sym_ent));

    strcpy(e->lexe, lex);
    strcpy(e->sym_type, stype);
    strcpy(e->dt_type, dtype);
    strcpy(e->scope, scope);

    e->size = dt_size(dtype);
    e->h_val = h;

    e->next = ST[h];
    ST[h] = e;
}

struct token getNextToken(FILE *fp) {
    struct token t;
    char buf[50];
    int ch, i;

    while((ch=fgetc(fp))!=EOF) {
        col_no++;

        if(ch=='\n'){ line_no++; col_no=0; continue; }
        if(isspace(ch)) continue;

        if(isalpha(ch)||ch=='_') {
            i=0; buf[i++]=ch;
            while(isalnum(ch=fgetc(fp))||ch=='_'){ buf[i++]=ch; col_no++; }
            buf[i]='\0'; ungetc(ch,fp);

            strcpy(t.tk_name,buf);
            strcpy(t.type,isKeyword(buf)?"kw":"id");
            t.row=line_no; t.col=col_no;
            return t;
        }

        if(isdigit(ch)) {
            while(isdigit(fgetc(fp)));
            strcpy(t.tk_name,"num");
            strcpy(t.type,"num");
            return t;
        }

        if(strchr("(){};,",ch)) {
            t.tk_name[0]=ch; t.tk_name[1]='\0';
            strcpy(t.type,"sym");
            return t;
        }
    }

    strcpy(t.type,"EOF");
    return t;
}

void displayST() {
    printf("\nGLOBAL SYMBOL TABLE\n");
    printf("Lexeme\tType\tDT\tSize\tHash\n");
    for(int i=0;i<TABSZ;i++)
        for(struct sym_ent *e=ST[i];e;e=e->next)
            if(strcmp(e->scope,"global")==0)
                printf("%s\t%s\t%s\t%d\t%d\n",
                       e->lexe,e->sym_type,e->dt_type,e->size,e->h_val);

    printf("\nLOCAL SYMBOL TABLES\n");
    for(int i=0;i<TABSZ;i++)
        for(struct sym_ent *e=ST[i];e;e=e->next)
            if(strcmp(e->scope,"global")!=0)
                printf("%s (%s)\t%s\t%s\t%d\t%d\n",
                       e->lexe,e->scope,e->sym_type,e->dt_type,e->size,e->h_val);
}

int main() {
    FILE *fp = fopen("q1in.c","r");
    if(!fp) return 1;

    for(int i=0;i<TABSZ;i++) ST[i]=NULL;

    struct token tok, next;
    char currType[10]="";
    char scope[20]="global";

    while(1) {
        tok = getNextToken(fp);
        if(strcmp(tok.type,"EOF")==0) break;

        if(strcmp(tok.type,"kw")==0 && dt_size(tok.tk_name)>0) {
            strcpy(currType,tok.tk_name);
        }
        else if(strcmp(tok.type,"id")==0 && currType[0]) {
            long pos = ftell(fp);
            next = getNextToken(fp);

            if(strcmp(next.tk_name,"(")==0) {
                insertST(tok.tk_name,"func",currType,"global");
                strcpy(scope,tok.tk_name);
            } else {
                insertST(tok.tk_name,"var",currType,scope);
            }
            fseek(fp,pos,SEEK_SET);
            currType[0]='\0';
        }
        else if(strcmp(tok.tk_name,"}")==0) {
            strcpy(scope,"global");
        }
    }

    fclose(fp);
    displayST();
    return 0;
}
