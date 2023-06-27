/*
 * App.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */
#ifndef APP_H_
#define APP_H_


#include "../CardModule/Card.h"
#include "../TerminalModule/Terminal.h"
#include "../ServerModule/Server.h"

ST_cardData_t CardData ;
ST_terminalData_t TerminalData;
ST_transaction_t ServerData;

void CardModule (void);
void TerminalModule (void);
void ServerModule (void);
void AppStart(void);

#endif

