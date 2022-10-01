#include "msp.h"


/**
 * main.c
 */

void GPIO_7_seg_display_init(){

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
