/*
 * Student_Mangement_Queue.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Ephraim
 */


/*
 * fifo.c
 *
 *  Created on: Sep 15, 2022
 *      Author: ff
 */
#include "Student_Mangement_Queue.h"


FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf)
{
	if(buf==NULL)
		return FIFO_null;

	fifo->base=buf;
	fifo->head=buf;
	fifo->tail=buf;
	fifo->length=width;
	fifo->count=0;

	return FIFO_no_error;


}
FIFO_Buf_Status FIFO_enqueue(FIFO_Buf_t *fifo,element_type* item)
{

	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	if(FIFO_IS_FULL(fifo)==FIFO_full)
		return FIFO_full;

	*(fifo->head)=*item;
	fifo->count++;

	//circular FIFO
	if(fifo->head ==(fifo->base+(fifo->length*4)-4))
		fifo->head=fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;

}
FIFO_Buf_Status FIFO_dequeue(FIFO_Buf_t *fifo,element_type *item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	if(fifo->count ==0)
		return FIFO_empty;

	*item =*(fifo->tail);

	fifo->count--;

	//circular FIFO
	if(fifo->tail ==(fifo->base+(fifo->length*4)-4))
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

