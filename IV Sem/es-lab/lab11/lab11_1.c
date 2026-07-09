"""Q1) Write a program to set the following intensity levels to the LED connected to 
PWM output. Use ROW-0 of keyboard for intensity variation. 
 
Intensity Key Pressed 
10% | 0 
25% | 1 
50% | 2 
75% | 3 
 
Program: """

#include <LPC17xx.h> 
int pulsewidth[] = {0,3000,7500,15000,22500}; 
int count=1; 
int dir=0; 
unsigned int temp3; 
void initPWM(void); 
void updatepulsewidth(unsigned int pulseWidth); 
void delayMS(unsigned int milliseconds); 
int scan(void); 
int main(void) 
{ 
 LPC_GPIO0->FIODIR |= 1<<8; 
 LPC_GPIO0->FIODIR &= ~(0xF<<4); 
 SystemInit(); 
 SystemCoreClockUpdate(); 
 initPWM(); 
 while(1) 
 { 
  count=scan(); 
  if(count==0x1) 
   updatepulsewidth(pulsewidth[1]); 
  else if(count==0x2) 
   updatepulsewidth(pulsewidth[2]); 
  else if(count==0x4) 
   updatepulsewidth(pulsewidth[3]); 
  else if(count==0x8) 
   updatepulsewidth(pulsewidth[4]); 
  delayMS(100000); 
 } 
} 
void initPWM(void) 
{ 
 LPC_PINCON->PINSEL3 |= 0x8000; 
 LPC_PWM1->PCR = 0x1000; 
 LPC_PWM1->PR = 0; 
 LPC_PWM1->MR0 = 30000; 
 LPC_PWM1->MCR = (1<<1); 
 LPC_PWM1->LER = 0xff; 
 LPC_PWM1->TCR = 0x00000002; 
 LPC_PWM1->TCR = 0x00000009; 
} 
void updatepulsewidth(unsigned int pulseWidth) 
{ 
 LPC_PWM1->MR4 = pulseWidth; 
 LPC_PWM1->LER = 0xff; 
} 
void delayMS(unsigned int milliseconds) 
{ 
 LPC_TIM0->CTCR = 0x0; 
 LPC_TIM0->PR = 2; 
 LPC_TIM0->TCR = 0x02; 
 LPC_TIM0->TCR = 0x01; 
 while(LPC_TIM0->TC < milliseconds);  
 LPC_TIM0->TCR = 0x00; 
} 
int scan(void) 
{ 
 LPC_GPIO0->FIOSET = 0x100; 
 temp3 = LPC_GPIO0->FIOPIN; 
 temp3 &= 0xF0; 
 if(temp3!=0) 
  return temp3>>4; 
 return 1; 
}

"""Observations: - The code sets up a PWM signal and adjusts its width based on certain conditions read 
from GPIO pins. - The `pulsewidth` array seems to hold predefined pulse width values for different 
conditions. 
 - The `initPWM()` function initializes the PWM peripheral, setting the necessary registers 
for its operation. It configures the PWM pin and sets the match register values. 
 - `updatepulsewidth()` function updates the pulse width of the PWM signal by setting the 
match register MR4. 
 - `delayMS()` function provides a delay in milliseconds using Timer0 of the LPC17xx. 
 - `scan()` function appears to read inputs from GPIO pins and return a value based on the 
input pattern. 
 - In `main()`, it repeatedly scans GPIO pins and updates the PWM pulse width based on 
the scanned input."""