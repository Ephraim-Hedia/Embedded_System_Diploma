/*
 * Student_Mangement_Queue.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Ephraim
 */

#ifndef STUDENT_MANGEMENT_QUEUE_H_
#define STUDENT_MANGEMENT_QUEUE_H_



#include "stdio.h"
#include "stdint.h"

#include "Student_Mangement_System.h"

typedef enum{
	FIFO_empty,
	FIFO_full,
	FIFO_no_error,
	FIFO_null
}FIFO_Buf_Status;

//USer Configuration

//Select The Element Type (uint8_t , uint16_t , uint32_t,.....)
#define element_type	sStudentDetail_t
#define width 50

element_type uart_buffer[width];


typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type *base;
	element_type *head;
	element_type *tail;
}FIFO_Buf_t;


//FIFO APIs
FIFO_Buf_Status FIFO_init(FIFO_Buf_t *fifo,element_type* buf);//Linking Array with Structure
FIFO_Buf_Status FIFO_enqueue(FIFO_Buf_t *fifo,element_type* item);
FIFO_Buf_Status FIFO_dequeue(FIFO_Buf_t *fifo,element_type *item);
FIFO_Buf_Status FIFO_IS_FULL(FIFO_Buf_t *fifo);





#endif /* STUDENT_MANGEMENT_QUEUE_H_ */
