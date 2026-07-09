"""Q1. Write an ARM assembly language program to convert a 32-bit BCD number in the unpacked 
form into packed form.

Source code:"""

 AREA RESET, DATA, READONLY 
 EXPORT __Vectors 
 
__Vectors 
    DCD 0X40001000   ; Defining Constant word 
    DCD Reset_Handler ; Reset vector 
    ALIGN 
 AREA mycode, CODE, READONLY 
 ENTRY 
 EXPORT Reset_Handler 
 
Reset_Handler 
    MOV R5, #4         ; Counter for looping through each byte 
    LDR R0, =NUM       ; Load the address of NUM into R0 
    MOV R4, #0         ; Initialize accumulator for packed BCD result 
    LDR R1, =RESULT    ; Load the address of RESULT into R1 
 
Loop 
    LDRB R2, [R0], #1  ; Load the next BCD digit from memory 
    MOV R3, #0         ; Temporary register for masking 
 
    ; Convert the BCD digit to packed BCD 
    LSL R4, R4, #4     ; Shift the packed result to make room for the new digit 
    AND R3, R2, #0xF   ; Mask the lower 4 bits of the BCD digit 
    ORR R4, R4, R3     ; Combine the result with the new digit 
 
    SUBS R5, R5, #1    ; Decrement the loop counter 
    BNE Loop           ; Branch back if not equal to zero 
 
    BX LR              ; Return from subroutine 
 
NUM     DCD 0x12345678  ; 32-bit BCD number 
RESULT  DCD 0x0          ; Result holder 
 
END