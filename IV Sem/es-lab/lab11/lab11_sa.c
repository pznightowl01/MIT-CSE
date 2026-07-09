"""Sample) Write a program to vary the intensity of an LED using PWM. 
Program:"""

#include<LPC17xx.h> 
void initPWM(void); 
void updatePulseWidth(unsigned int pulseWidth); 
void delayMS(unsigned int milliseconds); 
int main(void){ 
 int pulseWidths[]={0,3000,6000,9000,12000,15000,18000,21000,24000,27000}; 
 const int numPulseWidths=10; 
 int count=1; 
 int dir=0; 
 initPWM(); 
 while(1){ 
  updatePulseWidth(pulseWidths[count]); 
  delayMS(10000); 
  if(count==(numPulseWidths-1)|| count==0){ 
   dir=!dir; 
  } 
  if(dir)count--; 
  else count++; 
 } 
} 
 
void initPWM(void){ 
 LPC_PINCON->PINSEL3 |= 0x8000; 
 LPC_PWM1->PCR = 0x1000; 
 LPC_PWM1->PR = 0; 
 LPC_PWM1->MR0 = 30000; 
 LPC_PWM1->MCR = (1<<1); 
 LPC_PWM1->LER = 0xff; 
 LPC_PWM1->TCR = 0x00000002; 
 LPC_PWM1->TCR = 0x00000009; 
} 
 
void delayMS(unsigned int milliseconds){ 
 LPC_TIM0->CTCR = 0x0; 
 LPC_TIM0->PR = 2; 
 LPC_TIM0->TCR = 0x02; 
 LPC_TIM0->TCR = 0x01; 
 while(LPC_TIM0->TC < milliseconds); 
desired delay 
 LPC_TIM0->TCR = 0x00; 
} 

"""Observations: 
 
- The code initializes and utilizes PWM (Pulse Width Modulation) functionality of the LPC17xx microcontroller to control the width of pulses. 
- The initPWM() function initializes the PWM by configuring necessary registers such as PINSEL3, PCR, PR, MR0, MCR, LER, and TCR of the PWM peripheral. 
- It sets up PWM1 with a period of 30,000 clock cycles. 
- The delayMS() function configures and utilizes Timer 0 (TIM0) to generate delays in milliseconds. 
- Inside the main() function: 
- An array pulseWidths[] is defined with ten elements representing different pulse widths. 
- The program cyclically changes the pulse width in a loop, gradually increasing or decreasing it, depending on the value of dir. 
- The loop is structured to move through the pulseWidths array, increasing count until it 
reaches the last index, then reversing direction until it reaches the first index. 
- After setting the pulse width, there's a delay of 10,000 milliseconds. 
- The dir variable determines the direction of counting through the pulseWidths array."""