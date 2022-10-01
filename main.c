#include "msp.h"


/**
 * main.c
 */

void GPIO_7_seg_display_init(){
    //Set P8.2-5 to output for digits
    P8->DIR |= BIT2 | BIT3 | BIT4 | BIT5;
    //Set P4.0-6 to output for segments
    P4->DIR |= BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6;
}

void push_button_init(){

}

void NVIC_init(){

}

void integer_to_array(){

}

void display(){

}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	GPIO_7_seg_display_init();
	push_button_init();
	NVIC_init();

	while(1){
	    integer_to_array();
	    display();
	}
}
