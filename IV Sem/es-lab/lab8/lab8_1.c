"""Simulate DIE tossing on LCD  
Hint: program reads the external interrupt using the key sw2. A random 
number between 0-6 should be displayed on the LCD upon keypress.  
 
Program:"""

#include <lpc17xx.h> 
void switch_init(void); 
void lcd_init(void);  
void write(int, int);  
void delay_lcd(unsigned int);  
void lcd_comdata(int, int);   
void clear_ports(void);  
void lcd_puts(unsigned char *);  
int t = 0; 
int generate_random_throw() { 
  return rand()%6 + 1; 
} 
int main(void) {  
 
  unsigned char main[11] = "DIE:  "; 
  SystemInit();  
  SystemCoreClockUpdate();   
  lcd_init(); 
  switch_init(); 
  while (1) { 
    if (LPC_GPIO2->FIOPIN & 1 << 12) { 
      // off 
 
    } else { 
      // on 
      main[5] = generate_random_throw() + 0x30;   
      delay_lcd(80000);  
    } 
    lcd_comdata(0x80, 0); 
    lcd_puts(main); 
  
     
  }     
} 
void switch_init() { 
  LPC_PINCON->PINSEL4 &= 0xFDFFFFFF; 
  LPC_GPIO2->FIODIR &= 0xFFFFEFFF; 
} 
//lcd initialization  
void lcd_init() {  
  /*Ports initialized as GPIO */  
  LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28  
  /*Setting the directions as output */  
  LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;   
  clear_ports();  
  delay_lcd(3200);  
  lcd_comdata(0x33, 0);   
  delay_lcd(30000);   
  lcd_comdata(0x32, 0);  
  delay_lcd(30000);  
  lcd_comdata(0x28, 0); //function set  
  delay_lcd(30000);  
  lcd_comdata(0x0c, 0); //display on cursor off  
  delay_lcd(800);  
  lcd_comdata(0x06, 0); //entry mode set increment cursor right  
  delay_lcd(800);  
  lcd_comdata(0x01, 0); //display clear  
  delay_lcd(10000);  
  return;  
} 
void lcd_comdata(int temp1, int type) {  
  int temp2 = temp1 & 0xf0; //move data (26-8+1) times : 26 - HN place, 4 - Bits  
  temp2 = temp2 << 19; //data lines from 23 to 26  
  write(temp2, type);  
  temp2 = temp1 & 0x0f; //26-4+1  
  temp2 = temp2 << 23;   
  write(temp2, type);  
  delay_lcd(1000);  
  return;  
} 
void write(int temp2, int type) {   
  clear_ports();  
  LPC_GPIO0->FIOPIN = temp2; 
  if (type==0)   // Assign the value to the data lines  
    LPC_GPIO0->FIOCLR = 1<<27; // clear bit RS for Command 
  else  
    LPC_GPIO0->FIOSET = 1<<27; // set bit RS for Data  
  LPC_GPIO0->FIOSET = 1<<28; // EN=1  
  delay_lcd(25);  
  LPC_GPIO0->FIOCLR = 1<<28; // EN =0  
  return;  
} 
void delay_lcd(unsigned int r1) {  
  unsigned int r;  
  for(r=0;r<r1;r++);  
  return;  
} 
void clear_ports(void) {  
  /* Clearing the lines at power on */  
  LPC_GPIO0->FIOCLR = 0x0F<<23; //Clearing data lines  
  LPC_GPIO0->FIOCLR = 1<<27; //Clearing RS line  
  LPC_GPIO0->FIOCLR = 1<<28; //Clearing Enable line    
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

"""Observations and Conclusions: 
 - The code appears to be designed for an LPC17xx microcontroller, likely for a specific 
application involving a display and a switch. - The main function initializes the system, including the LCD display and a switch 
connected to pin P2.12. - The `generate_random_throw()` function generates a random number between 1 and 
6, simulating a die roll. - Inside the main loop, if the switch is pressed (P2.12 is low), it generates a random die 
throw and displays it on the LCD. - The LCD initialization sequence (`lcd_init()`) sets up the display for communication 
and configuration. 
- The `switch_init()` function initializes the switch pin as an input. - The `lcd_comdata()` function sends command or data to the LCD module. - The `write()` function writes data to the LCD data lines. - The `delay_lcd()` function introduces delays in the LCD operation. - The `clear_ports()` function clears the control lines of the LCD. - The `lcd_puts()` function writes a string to the LCD, scrolling to the second line if the 
string is longer than 16 characters. - Overall, the code initializes the system, detects switch input, generates a random 
number, and displays it on the LCD. However, there could be improvements such as 
debouncing the switch input, adding error handling, and optimizing delay functions 
for more accurate timing. Additionally, the LCD initialization and communication 
could be better organized for clarity and maintainability."""