"""Q1. Write a program to add ten 32-bit numbers available in code memory and store the 
result in data memory. 

Source code:"""

AREA RESET, DATA, READONLY 
EXPORT __Vectors 
 
__Vectors 
     DCD 0X10001000   ; Defining Constant word 
     DCD Reset_Handler ; Reset vector 
     ALIGN 
 
AREA mycode, CODE, READONLY 
ENTRY 
EXPORT Reset_Handler 
 
Reset_Handler 
       ; Define constants for loop counter and array size 
    MOV R6, #10        ; Number of 32-bit numbers to add 
    MOV R7, #40        ; Size of array (10 numbers * 4 bytes each) 
    LDR R0, =NUMBERS  ; Load the address of the array into R0 
    MOV R1, #0 ; Initialize sum to zero 
Loop:    ; Loop to add each number 
    LDR R2, [R0], #4  ; Load the current number from memory into R2 
    ADD R1, R1, R2   ; Add the current number to the sum 
 
     
    SUBS R6, R6, #1 ; Decrement the loop counter 
BNE Loop   ; Repeat the loop if the loop counter is not zero 
       ; Store the sum in the result memory location 
    LDR R3, =RESULT 
    STR R1, [R3] 
    B END   ; End of program 
 
AREA DATA, READWRITE 
NUMBERS 
    DCD 1, 2, 3, 4, 5, 6, 7, 8, 9, 10   ; 10 32-bit numbers to add 
RESULT 
    DCD 0                               ; Result placeholder 
 
END 