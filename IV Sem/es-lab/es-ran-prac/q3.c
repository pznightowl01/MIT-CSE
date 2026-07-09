#include <LPC17xx.h>

unsigned int i, value = 65535; 
unsigned seven_seg[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
unsigned int seg_select[4] = {0, 1<<23, 2<<23, 3<<23};

void display() {

    int digits[4] = {0,0,0,0};
    int ind = 0,x, val = value;
    while(val > 0) {
        x = val % 16;
        val = val / 16;
        digits[ind++] = x;
    }

    for(ind = 0; ind < 4; ind++) {
        LPC_GPIO1->FIOPIN = seg_select[ind];
        LPC_GPIO0->FIOPIN = seven_seg[digits[ind]] << 4;
	    for(i = 0; i < 100000; i++);
    }
}


int main(void) {
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_PINCON->PINSEL3 &= ~(0xF<<23);
	LPC_PINCON->PINSEL4 &= 0xFFFFFFF0;
	LPC_GPIO0->FIODIR |= 0xFF0;
	LPC_GPIO2->FIODIR &= ~(0);
	LPC_GPIO1->FIODIR |= 0xF << 23;
	LPC_GPIO1->FIOPIN = 0;
	while(1) {
	    for(i = 0; i < 1000; i++);
        if (LPC_GPIO2->FIOPIN & 1) 
            value += 1;
        else
            value -=1;
        if (value == 0)
            value = 65535;
        if (value == 65536)
            value = 0;
        display();
	}
}
