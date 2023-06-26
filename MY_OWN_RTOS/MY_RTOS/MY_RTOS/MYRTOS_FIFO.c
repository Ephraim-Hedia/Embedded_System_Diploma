/*
 * MYRTOS_FIFO.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */


#include "MYRTOS_FIFO.h"


FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf ,unsigned int length)
{
	if(buf==NULL)
		return FIFO_null;

	fifo->base=buf;
	fifo->head=buf;
	fifo->tail=buf;
	fifo->length=length;
	fifo->count=0;

	return FIFO_no_error;


}
FIFO_Buf_Status FIFO_enqueue(FIFO_Buf_t *fifo,element_type item)
{
	int end_fifo_buff=0;
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	if(FIFO_IS_FULL(fifo)==FIFO_full)
		return FIFO_full;

	*(fifo->head)=item;
	fifo->count++;

	//circular FIFO
	end_fifo_buff =(unsigned int)fifo->base+(unsigned int)(((fifo->length*4)-4));
	if((unsigned int)fifo->head ==(end_fifo_buff))
		fifo->head=fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;

}
FIFO_Buf_Status FIFO_dequeue(FIFO_Buf_t *fifo,element_type *item)
{
	int end_fifo_buff=0;
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	if(fifo->count ==0)
		return FIFO_empty;

	*item =*(fifo->tail);

	fifo->count--;

	//circular FIFO
	end_fifo_buff =(unsigned int)fifo->base+(unsigned int)(((fifo->length*4)-4));
	if((unsigned int)fifo->tail ==(end_fifo_buff))
		fifo->tail=fifo->base;
	else
		fifo->tail++;


	return FIFO_no_error;

}
FIFO_Buf_Status FIFO_IS_FULL(FIFO_Buf_t *fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
	return FIFO_null;

	if(fifo->count ==fifo->length)
		return FIFO_full;

	return FIFO_no_error;

}
