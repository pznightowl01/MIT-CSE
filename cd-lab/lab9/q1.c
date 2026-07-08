// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//Develop an SLR(1) Parser for the Given Expression Grammar and Demonstrate Parsing Actions
//E->E+T|T
//T-> T*F|F
//F-> ( E )|id

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATES 12
#define TERMS 6
#define NONTERMS 3

char terminals[] = {'+', '*', '(', ')', 'i', '$'};
char nonterminals[] = {'E', 'T', 'F'};

char prod_lhs[] = {'E','E','T','T','F','F'};
int prod_len[] = {3,1,3,1,3,1};

char action[STATES][TERMS][10];
int gototab[STATES][NONTERMS];

int stack[100];
int top = -1;

int get_terminal_index(char c) {
    for(int i=0;i<TERMS;i++)
        if(terminals[i]==c) return i;
    return -1;
}

int get_nonterminal_index(char c) {
    for(int i=0;i<NONTERMS;i++)
        if(nonterminals[i]==c) return i;
    return -1;
}

void init_table() {
    for(int i=0;i<STATES;i++)
        for(int j=0;j<TERMS;j++)
            strcpy(action[i][j],"err");

    strcpy(action[0][2],"s4"); strcpy(action[0][4],"s5");
    strcpy(action[1][0],"s6"); strcpy(action[1][5],"acc");
    strcpy(action[2][0],"r2"); strcpy(action[2][1],"s7");
    strcpy(action[2][3],"r2"); strcpy(action[2][5],"r2");
    strcpy(action[3][0],"r4"); strcpy(action[3][1],"r4");
    strcpy(action[3][3],"r4"); strcpy(action[3][5],"r4");
    strcpy(action[4][2],"s4"); strcpy(action[4][4],"s5");
    strcpy(action[5][0],"r6"); strcpy(action[5][1],"r6");
    strcpy(action[5][3],"r6"); strcpy(action[5][5],"r6");
    strcpy(action[6][2],"s4"); strcpy(action[6][4],"s5");
    strcpy(action[7][2],"s4"); strcpy(action[7][4],"s5");
    strcpy(action[8][0],"s6"); strcpy(action[8][3],"s11");
    strcpy(action[9][0],"r1"); strcpy(action[9][1],"s7");
    strcpy(action[9][3],"r1"); strcpy(action[9][5],"r1");
    strcpy(action[10][0],"r3"); strcpy(action[10][1],"r3");
    strcpy(action[10][3],"r3"); strcpy(action[10][5],"r3");
    strcpy(action[11][0],"r5"); strcpy(action[11][1],"r5");
    strcpy(action[11][3],"r5"); strcpy(action[11][5],"r5");

    for(int i=0;i<STATES;i++)
        for(int j=0;j<NONTERMS;j++)
            gototab[i][j] = -1;

    gototab[0][0]=1; gototab[0][1]=2; gototab[0][2]=3;
    gototab[4][0]=8; gototab[4][1]=2; gototab[4][2]=3;
    gototab[6][1]=9; gototab[6][2]=3;
    gototab[7][2]=10;
}

void preprocess(char *str) {
    for(int i=0; str[i]; i++) {
        if(str[i]=='i' && str[i+1]=='d') {
            for(int j=i+2; str[j]; j++)
                str[j-1]=str[j];
        }
    }
}

void print_stack() {
    for(int i=0;i<=top;i++)
        printf("%d ",stack[i]);
}

void parse(char *input) {
    top = 0;
    stack[top] = 0;
    int ip = 0;

    while(1) {
        int state = stack[top];
        char sym = input[ip];
        int t_index = get_terminal_index(sym);

        if(t_index == -1) {
            printf("\nInvalid symbol\n");
            return;
        }

        char *act = action[state][t_index];

        printf("\nStack: ");
        print_stack();
        printf("\tInput: %s\tAction: %s", input+ip, act);

        if(act[0]=='s') {
            int next = atoi(act+1);
            stack[++top] = next;
            ip++;
        }

        else if(act[0]=='r') {
            int prod = atoi(act+1);
            int len = prod_len[prod-1];
            top -= len;

            int cur_state = stack[top];
            char lhs = prod_lhs[prod-1];

            int nt_index = get_nonterminal_index(lhs);

            stack[++top] = gototab[cur_state][nt_index];

            printf(" (Reduce by %c)", lhs);
        }

        else if(strcmp(act,"acc")==0) {
            printf("\n\nString Accepted!\n");
            return;
        }

        else {
            printf("\n\nParsing Error\n");
            return;
        }
    }
}

int main() {
    char input[100];

    init_table();

    printf("Enter input (end with $): ");
    scanf("%s", input);

    preprocess(input);

    parse(input);

    return 0;
}
