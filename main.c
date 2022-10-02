#include "msp.h"
#include <stdio.h>



/**
 * main.c
 */
//Global Variables
int display[4] = {0,0,0,0};
int counter = 0;

void GPIO_7_seg_display_init(){
    //Set P8.2-5 to output for digits
    P8->DIR |= BIT2 | BIT3 | BIT4 | BIT5;
    //Set P4.0-6 to output for segments
    P4->DIR |= BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6;

    //Set P5.0 to output for negative indicator
    P5->DIR |= BIT0;
}

void push_button_init(){
    //Set P1.1 & P1.4 to input
    P1->DIR &= ~(BIT1 | BIT4);

    //Set P1.1 & P1.4 to GPIO
    P1->SEL0 &= ~(BIT1 | BIT4);
    P1->SEL1 &= ~(BIT1 | BIT4);
}

void NVIC_init(){
    //Set Interrupt on high-to-low transition
    P1->IES |= BIT1;
    P1->IES |= BIT4;

    P1->IFG = 0;//Clear all P1 Interrupt flags

    //Enable Interrupts
    P1->IE |= BIT1;
    P1->IE |= BIT4;

    //Enable Interrupts for Port 1 on NVIC
    NVIC->ISER[1] = 1 << (PORT1_IRQn - 32);
    NVIC->IP[35] = 0x0; //Set Port 1 to highest priority
}

void PORT1_IRQHandler(void){
    int temp = P1->IV; //Read Interrupt Flag Register

    if (temp == 4){ //If SW1 is pressed
        counter += 1;
    }
    if (temp == 10){ // If SW 2 is pressed
        counter -= 1;
    }
}

void integer_to_array(){
    //Convert Counter value to digits on the display
    int temp = counter;

    display[0] = temp / 1000;
    temp = temp % 1000;

    display[1] = temp / 100;
    temp = temp % 100;

    display[2] = temp / 10;
    temp = temp % 10;

    display[3] = temp;
}

void blank_LED(){
    P4->OUT = 0xFF;
}

void select_LED_Digit(int k){
    unsigned int LEDDigit[4]={~0b00000100, ~0x08, ~0x10, ~0x20}; //Digit Look-up Table
    P8->OUT = LEDDigit[3-k];
}

void output_segments(int digit){
    unsigned int sseg_table[16]={0b11000000,0b11111001,0b10100100,0b10110000,
                       0B10011001,0b10010010,0b010000010,0b11111000,
                       0b10000000,0b10010000,0b10001000,0b10000011,
                       0b11000110,0b10100001,0b10000110,0b10001110};

     P4->OUT = sseg_table[digit];
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
