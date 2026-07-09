"""2. Write an assembly language program to generate Fibonacci series. 
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
    MOV R0, #0         ; Initialize first Fibonacci number (F(0)) 
    MOV R1, #1         ; Initialize second Fibonacci number (F(1)) 
    MOV R2, #10        ; Number of Fibonacci numbers to generate (adjust as needed) 
 
Fibonacci_Loop 
    ; Output the current Fibonacci number 
    MOV R3, R0         ; Move the value of F(n) to R3 for output 
    ; (Code for outputting R3 to display or storing it as needed) 
 
    ; Calculate the next Fibonacci number: F(n+2) = F(n) + F(n+1) 
    ADD R3, R0, R1     ; Calculate F(n) + F(n+1) 
    MOV R0, R1         ; Update F(n) to the value of F(n+1) 
    MOV R1, R3         ; Update F(n+1) to the newly calculated Fibonacci number 
 
    SUBS R2, R2, #1    ; Decrement the loop counter 
    BNE Fibonacci Loop ; Continue loop if R2 is not equal to zero 
 
 B .     ; End of program 