#include "msp.h"


/**
 * main.c
 */
//Global Variables
int display[4] = {0,0,0,0};

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

void blank_LED(){

}

void select_LED_Digit(int k){

}

void output_segments(int digit){

}

void display_LED(int k){
    blank_LED();
    select_LED_Digit(k);
    output_segments(display[k]);
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	int k = 0; //Control Variable for Display Index

	GPIO_7_seg_display_init(); //Initialize Pins for the 7 Segment Display
	push_button_init(); //Initialize Pins for the Push Buttons
	NVIC_init();

	while(1){
	    integer_to_array();
	    display_LED(k);

	    //Increment k to move to the next digit of the display
        if (k>=3)
            k=0;
        else
            k+=1;
	}
}
