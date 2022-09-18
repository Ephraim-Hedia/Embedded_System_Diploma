/*
 * fifo.c
 *
 *  Created on: Sep 8, 2022
 *      Author: ff
 */

#include "fifo.h"


FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf,uint32_t length)
{
	if(buf==NULL)
		return FIFO_null;

	fifo->base =buf;
	fifo->head =buf;
	fifo->tail =buf;
	fifo->length =length;
	fifo->count =0;

	return FIFO_no_error;

}
FIFO_Buf_Status FIFO_enqueue (FIFO_Buf_t *fifo ,element_type item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	if(FIFO_IS_FULL(fifo)==FIFO_full)
		return FIFO_full;

	*(fifo->head)=item;
	fifo->count++;

	//circular FIFO
	if(fifo->head ==(fifo->base +(fifo->length *sizeof(element_type))))
		fifo->head=fifo->base;
	fifo->head++;

	return FIFO_no_error;
}
FIFO_Buf_Status FIFO_dequeue (FIFO_Buf_t *fifo ,element_type* item)
{
	if(!fifo->base || !fifo->head ||!fifo->tail)
		return FIFO_null;

	//Check if FIFO is Empty
	if(fifo->count ==0)
		return FIFO_empty;

	*item=*(fifo->tail);
	fifo->count--;

	if(fifo->tail ==(fifo->base +(fifo->length *sizeof(element_type))))
		fifo->tail=fifo->base;
	else
		fifo->tail++;

	return FIFO_no_error;

}
FIFO_Buf_Status FIFO_IS_FULL (FIFO_Buf_t *fifo )
{
	if(!fifo->base || !fifo->head ||!fifo->tail)
		return FIFO_null;
	if(fifo->count == fifo->length)
		return FIFO_full;

	return FIFO_no_error;

}
void FIFO_print (FIFO_Buf_t *fifo )
{
	int i;
	element_type* temp;

	if(fifo->count ==0)
	{
		printf("fifo is empty \n");
	}else{
		temp =fifo->tail;
		printf("\n=======FIFO_print=====\n");
		for(i=0;i<fifo->count;i++)
		{
			printf("\t %x\n",*temp);
			temp++;
		}
		printf("\n============\n");
	}
}
