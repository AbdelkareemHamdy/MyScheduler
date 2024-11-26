/*
 * OSMCAL_confg.h
 *
 *  Created on: Nov 25, 2023
 *      Author: Karim
 */

#ifndef OSMCAL_CONFG_H_
#define OSMCAL_CONFG_H_

#define DUMMY_XPSR              0x01000000U
#define DUMMY_LR                0xFFFFFFFD
#define MAX_TASK_NUM            5U
#define	HSI_CLK					16000000UL
#define	SYSTICK_TIM_CLK			HSI_CLK

#define NUMBER_OF_TASKS			5U

#define T1_STACK_START			(SRAM_END)
#define T2_STACK_START			((SRAM_END)- (1 * (SIZE_TASK_STACK)))
#define T3_STACK_START			((SRAM_END)- (2 * (SIZE_TASK_STACK)))
#define T4_STACK_START			((SRAM_END)- (3 * (SIZE_TASK_STACK)))
#define IDLE_TASK_STACK_STARTE	((SRAM_END)- (4 * (SIZE_TASK_STACK)))
#define SECED_STACK_START		((SRAM_END)- ((NUMBER_OF_TASKS) * (SIZE_TASK_STACK)))


#endif /* OSMCAL_CONFG_H_ */
