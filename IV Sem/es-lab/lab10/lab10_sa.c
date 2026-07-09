"""Sample) Write a program to configure and read analog data from 
ADC channel no 5, and display the digital data on LCD. 
 
Source Code:"""

#include <LPC17xx.h> 
#include <stdio.h> 
 
#define Ref_Vtg     3.300 
#define Full_Scale  0xFF 
 
void lcd_init(void); 
void lcd_comdata(int, int); 
void lcd_puts(unsigned char*); 
void delay_lcd(unsigned int); 
void write(int, int); 
void clear_ports(void); 
 
int main(void) { 
    unsigned long adc_temp; 
    float in_vtg; 
    unsigned char vtg[7]; 
    unsigned char Msg3[11] = {"ANALOG IP:"}; 
    SystemInit(); 
    SystemCoreClockUpdate(); 
 
    LPC_SC->PCONP |= (1 << 15); 
    LPC_SC->PCONP |= (1 << 12); 
 
    lcd_init(); 
 
    LPC_PINCON->PINSEL3 |= 0xC0000000; 
 
    lcd_comdata(0x80, 0); 
    delay_lcd(800); 
    lcd_puts(Msg3); 
 
    while (1) { 
        LPC_ADC->ADCR = (1 << 5) | (1 << 21) | (1 << 24); 
        while (!(LPC_ADC->ADGDR & (1 << 31))); 
        adc_temp = (LPC_ADC->ADGDR >> 4) & 0xFFF; 
        in_vtg = ((float)adc_temp * Ref_Vtg) / Full_Scale; 
        sprintf(vtg, "%3.2fV", in_vtg); 
 
        lcd_comdata(0xC0, 0); 
        delay_lcd(800); 
        lcd_puts(vtg); 
    } 
} 
 
void delay_lcd(unsigned int r) { 
    unsigned int t; 
    for (t = 0; t < r; t++); 
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
 
void write(int temp2, int type) { 
    clear_ports(); 
    LPC_GPIO0->FIOPIN = temp2; 
    if (type == 0) { 
        LPC_GPIO0->FIOCLR = 1 << 27; 
    } else { 
        LPC_GPIO0->FIOSET = 1 << 27; 
    } 
    LPC_GPIO0->FIOSET = 1 << 28; 
    delay_lcd(25); 
    LPC_GPIO0->FIOCLR = 1 << 28; 
    return; 
} 
 
void lcd_init() { 
    LPC_GPIO0->FIODIR |= 0xF << 23 | 1 << 27 | 1 << 28; 
    clear_ports(); 
    delay_lcd(3200); 
 
    lcd_comdata(0x33, 0); 
    delay_lcd(30000); 
 
    lcd_comdata(0x32, 0); 
    delay_lcd(30000); 
 
    lcd_comdata(0x28, 0); 
    delay_lcd(30000); 
 
    lcd_comdata(0x0C, 0); 
    delay_lcd(800); 
 
    lcd_comdata(0x06, 0); 
    delay_lcd(800); 
 
    lcd_comdata(0x01, 0); 
    delay_lcd(10000); 
} 
 
void clear_ports(void) { 
    LPC_GPIO0->FIOCLR = 0xF << 23; 
    LPC_GPIO0->FIOCLR = 1 << 27; 
    LPC_GPIO0->FIOCLR = 1 << 28; 
 
    return; 
} 
 
void lcd_puts(unsigned char* str) { 
    unsigned int temp3, i = 0; 
    while (str[i]) { 
        temp3 = str[i]; 
        lcd_comdata(temp3, 1); 
        i++; 
        if (i == 16) { 
            lcd_comdata(0xC0, 0); 
        } 
    } 
    return; 
}

"""Observations and Conclusions: 
 
- The code initializes and configures ADC channel 5 to read analog data. 
- It uses sprintf to convert the ADC value to voltage and stores it in the vtg array. 
- The LCD is initialized and set up to display the "ANALOG IP:" message at the 
beginning. 
- Inside the main loop, it continuously reads the ADC value, converts it to voltage, and 
displays it on the LCD. 
- The delay_lcd function is used for creating delays during LCD operations. 
- The write function writes data to the LCD, and the lcd_comdata function sends 
commands and data to the LCD. 
- The clear_ports function clears the ports connected to the LCD. 
- Overall, this code allows for the continuous monitoring and display of analog data from 
ADC channel 5 on an LCD screen. """