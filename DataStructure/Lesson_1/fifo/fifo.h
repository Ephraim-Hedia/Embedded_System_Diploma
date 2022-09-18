/*
 * fifo.h
 *
 *  Created on: Sep 8, 2022
 *      Author: ff
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"

//USER Configuration
//Select The Element Type (uint8_t , uint16_t , uint32_t , ....)
#define element_type uint8_t

//Create buffer
#define width 5
element_type uart_buffer [width];

//FIFO Data Types
typedef struct {
	unsigned int length;
	unsigned int count ;
	element_type* head ;
	element_type* tail ;
	element_type* base ;
}FIFO_Buf_t;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}FIFO_Buf_Status;


//FIFO APIs
FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf,uint32_t length);
FIFO_Buf_Status FIFO_enqueue (FIFO_Buf_t *fifo ,element_type item);
FIFO_Buf_Status FIFO_dequeue (FIFO_Buf_t *fifo ,element_type* item);
FIFO_Buf_Status FIFO_IS_FULL (FIFO_Buf_t *fifo );
void FIFO_print (FIFO_Buf_t *fifo );

#endif /* FIFO_H_ */
