#include "uart.h"

unsigned char string_buffer[100]="learn-in-depth:<Ephraim>";
unsigned char const string_buffer_2[100]="Tp Create a rodata Section";
void main (void)
{
	Uart_Send_String (string_buffer);
}
