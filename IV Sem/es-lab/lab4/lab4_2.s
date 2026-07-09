"""Q2. Convert a 32-bit packed BCD number into its equivalent hexadecimal number. 
Source code:"""

 AREA RESET, DATA, READONLY 
 EXPORT __Vectors 
  
__Vectors  
 DCD 0x10001000  
 DCD Reset_Handler  
 ALIGN 
 AREA mycode, CODE, READONLY 
 ENTRY 
 EXPORT Reset_Handler 
Reset_Handler 
 LDR R0, =SRC  
 LDR R1, =DST  
 MOV R2, #0  
 MOV R3, #0  
convert 
 LDRB R4, [R0], #1  
 LSL R3, R3, #4  
 ORR R3, R3, R4  
 ADD R2, R2, #1  
 CMP R2, #8  
 BNE convert 
 STR R3, [R1]  
 B STOP 
SRC DCD 22090511 
DST DCD 0  
STOP B STOP 
 END