/*
 * lifo.c
 *
 *  Created on: Sep 7, 2022
 *      Author: ff
 */

#include "lifo.h"
#include "stdio.h"

LIFO_status LIFO_Add_item(LIFO_Buf_t *lifo_buf,element_type item)
{
	//Check LIFO is Valid
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_Null;


	//Check LIFO is FUll ?
//	if(lifo_buf->head >= (lifo_buf->base + (lifo_buf->length *4) ))
	if(lifo_buf->count ==lifo_buf->length)
		return LIFO_full;

	//Add Value
	*(lifo_buf->head)=item;
	lifo_buf->head++;
	lifo_buf->count++;

	return LIFO_no_error;

}
LIFO_status LIFO_get_item(LIFO_Buf_t *lifo_buf,element_type* item)
{
	//Check LIFO is Valid
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_Null;

	//check LIFO is Empty
//	if(lifo_buf->base == lifo_buf->head);
	if(lifo_buf->count==0)
		return LIFO_empty;

	lifo_buf->head --;
	*item=*(lifo_buf->head);
	lifo_buf->count--;

	return LIFO_no_error;
}
LIFO_status LIFO_init(LIFO_Buf_t *lifo_buf,element_type *buf,unsigned length)
{
	if(buf==NULL)
		return LIFO_Null;
	lifo_buf->base=buf;
	lifo_buf->head=buf;
	lifo_buf->length=length;
	lifo_buf->count=0;

	return LIFO_no_error;
}

