// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//4.S →(L) | a
//L → L,S | S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr=0;
char str[100];

void S();
void L();
void Lprime();

void invalid(){
    printf("ERROR\n");
    exit(0);
}

void valid(){
    printf("SUCCESS\n");
    exit(0);
}
void Lprime();
void S(){
    if (str[curr] == '('){
        curr++;
        L();
        if (str[curr] == ')'){
            curr++;
            return;
        } else {
            invalid();
        }
    }
    else if (str[curr] == 'a'){
        curr++;
        return;
    }
    else {
        invalid();
    }
}
void Lprime();
void L(){
    S();
    Lprime();
}

void Lprime() {
    if (str[curr] == ','){
        curr++;
        S();
        Lprime();
    }
    return;
}

int main(){
    printf("enter string: ");
    scanf("%s", str);

    S();

    if (str[curr] == '$')
        valid();
    else
        invalid();

    return 0;
}

