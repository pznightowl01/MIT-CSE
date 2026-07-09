"""3. Write an assembly language program to find GCD and LCM of two 8-bit numbers 
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
    MOV R0, #15       ; First 8-bit number (replace with your value) 
    MOV R1, #25       ; Second 8-bit number (replace with your value) 
 
    ; Find GCD 
    BL GCD 
     
    ; Result is in R0, store it in memory if needed 
     
    ; Find LCM 
    BL LCM 
     
    ; Result is in R0, store it in memory if needed 
     
    ; End of the program 
    B . 
 
; Function to find GCD of two numbers 
GCD 
    CMP R0, #0 
    BEQ EndGCD 
    CMP R1, #0 
    BEQ EndGCD 
 
    CMP R0, R1 
    BEQ EndGCD 
 
    BLT SwapGCD 
 
    SUBS R0, R0, R1 
    B GCD 
 
SwapGCD 
    MOV R2, R0 
    MOV R0, R1 
    MOV R1, R2 
    B GCD 
 
EndGCD 
    BX LR 
 
; Function to find LCM of two numbers 
LCM 
    MOV R3, R0       ; Save the original values 
    MOV R4, R1 
 
    BL GCD           ; Call GCD function to find GCD of the numbers 
 
    MOV R2, R0       ; Result of GCD is stored in R0 
 
    ; Calculate LCM: LCM(a, b) = (a * b) / GCD(a, b) 
    MUL R0, R3, R4   ; Multiply the original values 
    SDIV R0, R0, R2  ; Divide by GCD 
 
    BX LR