/*
 * MYRTOS_FIFO.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Ephraim
 */

#ifndef INC_MYRTOS_FIFO_H_
#define INC_MYRTOS_FIFO_H_

#include "stdio.h"
#include "stdint.h"
#include "Scheduler.h"

typedef enum{
	FIFO_empty,
	FIFO_full,
	FIFO_no_error,
	FIFO_null
}FIFO_Buf_Status;

//USer Configuration

//Select The Element Type (uint8_t , uint16_t , uint32_t,.....)
#define element_type	Task_ref*

typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type *base;
	element_type *head;
	element_type *tail;
}FIFO_Buf_t;


//FIFO APIs
FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf ,unsigned int length);//Linking Array with Structure
FIFO_Buf_Status FIFO_enqueue(FIFO_Buf_t *fifo,element_type item);
FIFO_Buf_Status FIFO_dequeue(FIFO_Buf_t *fifo,element_type *item);
FIFO_Buf_Status FIFO_IS_FULL(FIFO_Buf_t *fifo);
void FIFO_print(FIFO_Buf_t *fifo);



#endif /* INC_MYRTOS_FIFO_H_ */
