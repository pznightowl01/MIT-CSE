// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//3.S→aAcBe
//A→Ab|b
//B→d

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr=0;
char str[100];

void S();
void A();
void B();

void invalid() {
    printf("ERROR\n");
    exit(0);
}

void valid() {
    printf("SUCCESS\n");
    exit(0);
}

void S() {
    if (str[curr] == 'a') {
        curr++;
        A();
        if (str[curr] == 'c') {
            curr++;
            B();
            if (str[curr] == 'e')
                curr++;
            else
                invalid();
        } else {
            invalid();
        }
    } else {
        invalid();
    }
}

void A() {
    if (str[curr] == 'b') {
        curr++;
        while (str[curr] == 'b')
            curr++;
    } else {
        invalid();
    }
}

void B() {
    if (str[curr] == 'd')
        curr++;
    else
        invalid();
}

int main() {
    printf("enter string: ");
    scanf("%s", str);

    S();

    if (str[curr] == '$')
        valid();
    else
        invalid();

    return 0;
}
