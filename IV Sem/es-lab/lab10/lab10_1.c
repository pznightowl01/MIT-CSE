"""Q1) Write a  program to display the digital value representing the 
difference in analog voltages at ADC channel 4 and channel 5 on LCD 
using BURST and software mode 
 
Source Code:"""

 
#include <LPC17xx.h> 
#include <stdio.h> 
 
#define Ref_Vtg 3.300 
#define Full_Scale 0xFFF 
 
void delay_lcd(unsigned int r1) { 
    unsigned int r; 
    for(r=0;r<r1;r++); 
    return; 
} 
 
void clear_ports(void) { 
 
    LPC_GPIO0->FIOCLR = 0x0F<<23; 
    LPC_GPIO0->FIOCLR = 1<<27; 
    LPC_GPIO0->FIOCLR = 1<<28; 
     
    return; 
} 
 
void write(int temp2, int type) {  
    clear_ports(); 
    LPC_GPIO0->FIOPIN = temp2; 
    if(type==0) 
        LPC_GPIO0->FIOCLR = 1<<27; 
    else 
        LPC_GPIO0->FIOSET = 1<<27; 
    LPC_GPIO0->FIOSET = 1<<28; 
    delay_lcd(25); 
    LPC_GPIO0->FIOCLR = 1<<28; 
    return; 
} 
 
void lcd_comdata(int temp1, int type) { 
    int temp2 = temp1 & 0xF0; 
    temp2 = temp2 << 19; 
    write(temp2, type); 
    temp2 = temp1 & 0x0F; 
    temp2 = temp2 << 23;  
    write(temp2, type); 
    delay_lcd(1000); 
    return; 
} 
 
void lcd_puts(unsigned char *buf1) { 
    unsigned int i=0; 
    unsigned int temp3; 
    while(buf1[i]!='\0') { 
        temp3 = buf1[i]; 
        lcd_comdata(temp3, 1); 
        i++; 
        if(i==16) { 
            lcd_comdata(0xc0, 0); 
        } 
    } 
    return; 
} 
 
void lcd_init() { 
    LPC_PINCON->PINSEL1 &= 0xFC003FFF; 
    LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28; 
  
    clear_ports(); 
    delay_lcd(3200); 
    lcd_comdata(0x33, 0);  
    delay_lcd(30000);  
    lcd_comdata(0x32, 0); 
    delay_lcd(30000); 
    lcd_comdata(0x28, 0); 
    delay_lcd(30000); 
    lcd_comdata(0x0c, 0); 
    delay_lcd(800); 
    lcd_comdata(0x06, 0); 
    delay_lcd(800); 
    lcd_comdata(0x01, 0); 
    delay_lcd(10000); 
    return; 
} 
 
int main(void) 
{ 
    unsigned long adc_temp1, adc_temp2; 
    unsigned int i; 
    float in_vtg1, in_vtg2; 
    unsigned char vtg1[7], vtg2[7]; 
    unsigned char Msg3[6] = {"CH 4: "}; 
    unsigned char Msg4[6] = {"CH 5: "}; 
    SystemInit(); 
    SystemCoreClockUpdate(); 
    LPC_SC->PCONP |= (1 << 15); 
    lcd_init(); 
    LPC_PINCON->PINSEL3 |= 0x30000000; 
    LPC_PINCON->PINSEL3 |= 0xC0000000; 
    LPC_SC->PCONP |= (1 << 12); 
    SystemCoreClockUpdate(); 
    lcd_comdata(0x80, 0); 
    delay_lcd(800); 
    lcd_puts(&Msg3[0]); 
    lcd_comdata(0xC0, 0); 
    delay_lcd(800); 
    lcd_puts(&Msg4[0]); 
    LPC_ADC->ADCR = (1 << 4) | (1 << 5) | (1 << 21) | (1 << 16); 
    while (1) 
    { 
        while (!(LPC_ADC->ADDR5 & (1 << 31))); 
        adc_temp1 = LPC_ADC->ADDR4; 
        adc_temp1 >>= 4; 
        adc_temp1 &= 0xFFF; 
        adc_temp2 = LPC_ADC->ADDR5; 
        adc_temp2 >>= 4; 
        adc_temp2 &= 0x00000FFF; 
        in_vtg1 = (((float)adc_temp1 * (float)Ref_Vtg)) / ((float)Full_Scale); 
        in_vtg2 = (((float)adc_temp2 * (float)Ref_Vtg)) / ((float)Full_Scale); 
        printf(vtg1, "%3.2fV", in_vtg1); 
        printf(vtg2, "%3.2fV", in_vtg2); 
        for (i = 0; i < 2000; i++); 
        lcd_comdata(0x89, 0); 
        delay_lcd(800); 
        lcd_puts(&vtg1[0]); 
        lcd_comdata(0xC8, 0); 
        delay_lcd(800); 
        lcd_puts(&vtg2[0]); 
        for (i = 0; i < 200000; i++); 
        for (i = 0; i < 7; i++) 
            vtg1[i] = vtg2[i] = 0; 
        adc_temp1 = 0; 
        in_vtg1 = 0; 
        adc_temp2 = 0; 
        in_vtg2 = 0; 
    } 
}

"""Observations and Conclusions: 
 
- The code initializes an LCD display and two ADC channels (channel 4 and channel 5). 
- It continuously reads the analog voltage from both channels and converts them to digital 
values. 
- The digital values are then converted back to voltages and displayed on the LCD. 
- The code utilizes a delay function for timing purposes and functions to write data to the 
LCD. 
- It properly configures the pins for ADC and LCD operations. 
- The main loop continuously updates the LCD with the voltages read from the ADC 
channels."""