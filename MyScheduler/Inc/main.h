/*
 * main.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Karim
 */

#ifndef MAIN_H_
#define MAIN_H_


#define SIZE_TASK_STACK			1024U
#define SIZE_SECED_STACK		1024U


#define SRAM_START				0x20000000U
#define SIZE_SRAM				(128*1024)
#define SRAM_END				(SRAM_START+SIZE_SRAM)
#include "OSMCAL_confg.h"

void Task1_Handler(void);
void Task2_Handler(void);
void Task3_Handler(void);
void Task4_Handler(void);

#endif /* MAIN_H_ */
