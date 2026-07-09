// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//design RD parser to parse array declarations and expression statements with error reporting.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "la.h"

tk ct;
FILE *fp;

void error(char *s){
    printf("Syntax Error: Expected %s at row %d col %d\n",s,ct.row,ct.col);
    exit(1);
}

void match(char *s){
    if(strcmp(ct.token_name,s)==0 || (strcmp(s,"id")==0 && strcmp(ct.token_type,"id")==0) || (strcmp(s,"num")==0 && strcmp(ct.token_type,"num")==0))
        ct=getNextToken(fp);
    else
        error(s);
}

void factor();
void expn();

void identifier_list(){
    match("id");
    if(strcmp(ct.token_name,"[")==0){
        match("[");
        match("num");
        match("]");
    }
    if(strcmp(ct.token_name,",")==0){
        match(",");
        identifier_list();
    }
}

void declarations(){
    if(strcmp(ct.token_name,"int")==0 || strcmp(ct.token_name,"char")==0){
        ct=getNextToken(fp);
        identifier_list();
        match(";");
        declarations();
    }
}

void tprime(){
    if(strcmp(ct.token_name,"*")==0 || strcmp(ct.token_name,"/")==0 || strcmp(ct.token_name,"%")==0){
        ct=getNextToken(fp);
        factor();
        tprime();
    }
}

void term(){
    factor();
    tprime();
}

void seprime(){
    if(strcmp(ct.token_name,"+")==0 || strcmp(ct.token_name,"-")==0){
        ct=getNextToken(fp);
        term();
        seprime();
    }
}

void simple_expn(){
    term();
    seprime();
}

void eprime(){
    if(strcmp(ct.token_name,"==")==0 || strcmp(ct.token_name,"!=")==0 || strcmp(ct.token_name,"<")==0 || strcmp(ct.token_name,">")==0 || strcmp(ct.token_name,"<=")==0 || strcmp(ct.token_name,">=")==0){
        ct=getNextToken(fp);
        simple_expn();
    }
}

void expn(){
    simple_expn();
    eprime();
}

void factor(){
    if(strcmp(ct.token_type,"id")==0)
        match("id");
    else
        match("num");
}

void assign_stat(){
    match("id");
    match("=");
    expn();
}

void statement(){
    assign_stat();
    match(";");
}

void statement_list(){
    if(strcmp(ct.token_type,"id")==0){
        statement();
        statement_list();
    }
}

void program(){
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    statement_list();
    match("}");
}

int main(){
    fp=fopen("eval.c","r");
    ct=getNextToken(fp);
    program();
    printf("Parsing Successful\n");
}
