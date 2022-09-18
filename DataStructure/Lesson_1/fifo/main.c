/*
 * main.c
 *
 *  Created on: Sep 8, 2022
 *      Author: ff
 */

#include "fifo.h"


int main ()
{
	FIFO_Buf_t FIFO_UART;
	element_type i,temp;
	if(FIFO_init(&FIFO_UART,uart_buffer,5)==FIFO_no_error)
		printf("FIFO init ---Done \n");

	for (i=0;i<7;i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART,i)==FIFO_no_error)
			printf("FIFO enqueue -----Done \n");
		else
			printf("FIFO enqueue ----- Failed\n");
	}

	FIFO_print(&FIFO_UART);


	if(FIFO_dequeue(&FIFO_UART,&temp)==FIFO_no_error)
		printf("FIFO dequeue %x -----Done \n",temp);

	if(FIFO_dequeue(&FIFO_UART,&temp)==FIFO_no_error)
		printf("FIFO dequeue %x -----Done \n",temp);

	FIFO_print(&FIFO_UART);
	return 0;
}
