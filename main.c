#include "msp.h"


/**
 * main.c
 */

void 7_seg_display_init(){

}

void push_button_init(){

}

void NVIC(){

}

void integer_to_array(){

}

void display(){

}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	7_seg_display_init();
	push_button_init();
	NVIC();

	while(1){
	    integer_to_array();
	    display();
	}
}
