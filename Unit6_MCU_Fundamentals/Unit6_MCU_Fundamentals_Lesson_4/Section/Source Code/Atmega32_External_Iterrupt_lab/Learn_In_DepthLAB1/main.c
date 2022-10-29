/*
 * Learn_In_DepthLAB1.c
 *
 * Created: 10/29/2022 2:03:00 PM
 * Author : ff
 */ 



typedef unsigned char uint8_t;

#define F_CPU 8000000UL
#include <util/delay.h>

/***************************************/
/******* DIO Register ******************/
/***************************************/

//PORTA registers
#define PORTA	*((volatile uint8_t *)0x3B)	//8 Bit Register
#define DDRA	*((volatile uint8_t *)0x3A)	//8 Bit Register
#define PINA	*((volatile uint8_t *)0x39)	//8 Bit Register
//PORTB registers
#define PORTB	*((volatile uint8_t *)0x38)	//8 Bit Register
#define DDRB	*((volatile uint8_t *)0x37)	//8 Bit Register
#define PINB	*((volatile uint8_t *)0x36)	//8 Bit Register
//PORTA registers
#define PORTC	*((volatile uint8_t *)0x35)	//8 Bit Register
#define DDRC	*((volatile uint8_t *)0x34)	//8 Bit Register
#define PINC	*((volatile uint8_t *)0x33)	//8 Bit Register
//PORTA registers
#define PORTD	*((volatile uint8_t *)0x32)	//8 Bit Register
#define DDRD	*((volatile uint8_t *)0x31)	//8 Bit Register
#define PIND	*((volatile uint8_t *)0x30)	//8 Bit Register

/******************************************************/
/******* External Interrupt Register ******************/
/******************************************************/

#define MCUCR	*((volatile uint8_t *)0x55)		//8 Bit Register //MCU Control Register
#define MCUCSR	*((volatile uint8_t *)0x54)		//8 Bit Register //MCU Control and Status Register
#define GICR	*((volatile uint8_t *)0x5B)		//8 Bit Register //General Interrupt Control Register
#define GIFR	*((volatile uint8_t *)0x5A)		//8 Bit Register //General Interrupt Flag Register

/******************************************************/
/******* Global Interrupt Register ********************/
/******************************************************/
#define SREG	*((volatile uint8_t *)0x5f) //8 Bit Register







//External Interrupt Vectors
//External Interrupt Request 0
#define ISR_EXT_INT0	__vector_1
//External Interrupt Request 1
#define ISR_EXT_INT1	__vector_2
//External Interrupt Request 2
#define ISR_EXT_INT2	__vector_3


//ISR Definition
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)

void DIO_init(void)
{
	//Set pin 2 in PORTB as INPUT to config INT2
	DDRB &=~(1<<2);
	//Set pin 2 in PORTD as INPUT to config INT0
	DDRD &=~(1<<2);
	//Set pin 3 in PORTD as INPUT to config INT1
	DDRD &=~(1<<3);
	
	//Configuration for LEDS
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
	
}
void EXTI_init()
{
	//For Interrupt 0
//	Table 35. Interrupt 0 Sense Control
//	0 1 Any logical change on INT0 generates an interrupt request.

	MCUCR |=(1<<0);
	MCUCR &=~ (1<<1);
	
	

//	Table 34. Interrupt 1 Sense Control
//  1 1 The rising edge of INT0 generates an interrupt request.
	MCUCR |=(1<<2);
	MCUCR |=(1<<3);
	
//• Bit 6 – ISC2: Interrupt Sense Control 2
//If ISC2 is written to zero, a falling edge on INT2 activates the interrupt. If ISC2 is written to one, a rising edge on
//INT2 activates the interrupt.
	MCUCSR &=~(1<<6);
	
	
	//Enable External Interrupt (INT0,INT1,INT2)
	GICR|=(1<<5);
	GICR|=(1<<6);
	GICR|=(1<<7);
	
	//Enable Global Interrupt
	SREG |=(1<<7);
}
int main(void)
{
    DIO_init();
	EXTI_init();
	
    while (1) 
    {
		PORTD &=~(1<<5);
		PORTD &=~(1<<6);
		PORTD &=~(1<<7);
    }
}

ISR(ISR_EXT_INT0)
{
	PORTD |=(1<<5);
	_delay_ms(1000);
}


ISR(ISR_EXT_INT1)
{
	PORTD |=(1<<6);
	_delay_ms(1000);
}


ISR(ISR_EXT_INT2)
{
	PORTD |=(1<<7);
	_delay_ms(1000);
}