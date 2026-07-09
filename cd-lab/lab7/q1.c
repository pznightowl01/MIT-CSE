// Name : Princita Zina Miranda
// Section : SCE-C
// Reg No. : 220905115 (Roll No. 17)

//design RD parser

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

void identifier_list(){
    match("id");
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

void assign_stat(){
    match("id");
    match("=");
    if(strcmp(ct.token_type,"id")==0)
        match("id");
    else
        match("num");
    match(";");
}

void program(){
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    match("}");
}

int main(){
    fp=fopen("q1in.c","r");
    ct=getNextToken(fp);
    program();
    printf("Parsing Successful\n");
}
