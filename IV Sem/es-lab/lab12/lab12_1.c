"""Q1) Write a C program to rotate the stepper motor in the clockwise direction when SW2 is 
high and anticlockwise direction when SW2 is low.

Program:"""

#include <LPC17xx.h> 
unsigned long int var1,var2; 
unsigned int i=0,j=0,k=0; 
void clockwise() 
{ 
 var1=0x8; 
 for(i=0;i<=3;i++) 
 { 
  var1 <<=1; 
  LPC_GPIO0->FIOPIN=var1; 
  for(k=0;k<1000;k++); 
 } 
} 
 
void anti_clockwise() 
{ 
 var1=0x100; 
 for(i=0;i<=3;i++) 
 { 
  var1 >>=1; 
  LPC_GPIO0->FIOPIN=var1; 
  for(k=0;k<1000;k++); 
 } 
} 
 
 
int main() 
{ 
 SystemInit(); 
 SystemCoreClockUpdate(); 
  
 LPC_GPIO0->FIODIR=0xF<<4; 
 LPC_GPIO2->FIODIR &=0xFFFFEFFF; 
 while(1) 
 { 
  if(!(LPC_GPIO2->FIOPIN&1<<12)) 
  { 
   for(j=0;j<50;j++) 
   { 
    clockwise(); 
   } 
   for(k=0;k<6500;k++); 
  } 
  else 
  { 
   for(j=0;j<50;j++) 
   { 
    anti_clockwise(); 
   } 
   for(k=0;k<6500;k++); 
  } 
 } 
  
 return 0; 
}

"""Observations:
- The clockwise() function rotates the device in a clockwise direction by shifting a value (`var1`) leftward and updating the GPIO output (`LPC_GPIO0->FIOPIN`) accordingly.
- The anti_clockwise() function rotates the device in an anti-clockwise direction by shifting 
the value rightward and updating the GPIO output.
- The main() function initializes the system, sets the direction of GPIO pins, and enters an infinite loop where it checks the input from pin 12 of port 2.
- If pin 12 is low, it executes the clockwise() function for 50 iterations, presumably to rotate 
the device clockwise. It then waits for a short period before repeating. 
- If pin 12 is high, it executes the anti_clockwise() function for 50 iterations, presumably to rotate the device anti-clockwise. It then waits for a short period before repeating.
- There are delays after each rotation loop (`for(k=0;k<6500;k++);`) which seem to serve as pause intervals between rotations.
- The specific pin configurations and delay values may need to be adjusted based on the requirements of the stepper motor."""