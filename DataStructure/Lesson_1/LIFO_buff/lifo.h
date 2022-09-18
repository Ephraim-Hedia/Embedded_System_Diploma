/*
 * lifo.h
 *
 *  Created on: Sep 7, 2022
 *      Author: ff
 */

#ifndef LIFO_H_
#define LIFO_H_
#include "stdlib.h"
#include "stdint.h"

//type Definitions
#define element_type	uint8_t
#define width 5
element_type buffer[width];


//Select The Element Type (uint8_t , uint16_t , uint32_t,.....)

typedef struct {
	unsigned int length ;
	unsigned int count ;
	element_type *base ;
	element_type* head ;
}LIFO_Buf_t;

typedef enum{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null
}LIFO_status;

//APIs
LIFO_status LIFO_Add_item(LIFO_Buf_t *lifo_buf,element_type item);
LIFO_status LIFO_get_item(LIFO_Buf_t *lifo_buf,element_type* item);
LIFO_status LIFO_init(LIFO_Buf_t *lifo_buf,element_type *buf,unsigned length);



#endif /* LIFO_H_ */
