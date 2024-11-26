/*
 * OSMCAL_program.c
 *
 *  Created on: Nov 25, 2023
 *      Author: Karim
 */
#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "main.h"
#include "OSMCAL_confg.h"
#include "OSMCAL_interface.h"
void IdleTaskHandler(void);
typedef enum
{
	Ready_State,
	BlockedState,
}TaskState_t;
typedef struct
{
	uint32_t PSPValue;
	uint32_t BlockCount;
	TaskState_t CurrentState;
	void(*TaskHandler)(void);
}TCB_t;

TCB_t UserTasks[MAX_TASK_NUM];
/*Task pointers init*/
uint32_t Task_pu32PointerPSPVal[MAX_TASK_NUM]={T1_STACK_START,T2_STACK_START,T3_STACK_START,T4_STACK_START};
uint32_t GlobalTickCounter=0;
uint8_t CurrenTask=1U;/*Starting from 1*/
#define SET_PENDSV_PENDING_FLAG			((SCB->SCB_ICSR)|=(0b1<<28) )
#define CLEAR_PENDSV_PENDING_FLAG		((SCB->SCB_ICSR)|=(0b1<<27) )

void InitTasksStack(void)
{
	uint32_t * Local_TASK_PSP;
	uint8_t Local_countre1,Local_countre2;

	UserTasks[0].PSPValue = IDLE_TASK_STACK_STARTE;
	UserTasks[1].PSPValue = T1_STACK_START;
	UserTasks[2].PSPValue = T2_STACK_START;
	UserTasks[3].PSPValue = T3_STACK_START;
	UserTasks[4].PSPValue = T4_STACK_START;

	/**/
	UserTasks[0].TaskHandler=&IdleTaskHandler;
	UserTasks[1].TaskHandler=&Task1_Handler;
	UserTasks[2].TaskHandler=&Task2_Handler;
	UserTasks[3].TaskHandler=&Task3_Handler;
	UserTasks[4].TaskHandler=&Task4_Handler;

	for(Local_countre1=0;Local_countre1<MAX_TASK_NUM;Local_countre1++)
	{
		/*Init tasks as ready*/
		UserTasks[Local_countre1].CurrentState = Ready_State;
		Local_TASK_PSP=(uint32_t*)UserTasks[Local_countre1].PSPValue;
		Local_TASK_PSP--;
		*Local_TASK_PSP =DUMMY_XPSR;
		Local_TASK_PSP--;
		*Local_TASK_PSP =UserTasks[Local_countre1].TaskHandler;
		Local_TASK_PSP--;
		*Local_TASK_PSP =DUMMY_LR;
		for(Local_countre2=0;Local_countre2<13;Local_countre2++)
		{

			Local_TASK_PSP--;
			*Local_TASK_PSP =0;
		}
		UserTasks[Local_countre1].PSPValue=(uint32_t)(Local_TASK_PSP);
	}
}
/*
{


	uint32_t Local_u32TaskHandler[MAX_TASK_NUM]={Task1_Handler,Task2_Handler,Task3_Handler,Task4_Handler};
	uint8_t Local_u8LoopIdx1,Local_u8LoopIdx2;
	for ( Local_u8LoopIdx1 = 0; Local_u8LoopIdx1 < MAX_TASK_NUM; Local_u8LoopIdx1++)
	{
		*(--Task_pu32PointerPSPVal[Local_u8LoopIdx1]) = DUMMY_XPSR; /*push XPSR value
		*(--Task_pu32PointerPSPVal[Local_u8LoopIdx1])=Local_u32TaskHandler[Local_u8LoopIdx1];/*Puch pc Value
		*(--Task_pu32PointerPSPVal[Local_u8LoopIdx1])=DUMMY_LR;/*Puch LR Value
		for ( Local_u8LoopIdx2 = 0; Local_u8LoopIdx2 < 13; Local_u8LoopIdx2++)
		{
			*(--Task_pu32PointerPSPVal[Local_u8LoopIdx1])=0x00000000;/*Puch R0--->R12 Value
		}
	}
}
*/
void Stack_voidEnableSystenFaultsExcp(void)
{
	SCB->SCB_SHCSR|=(0b111<<16);/*16 Memmanage fault,17 Bus fault ,18 usage fault enable all */
}
/******************************HELPER FUNICTIONS*********************************************/
void _void2SavePSPValue(uint32_t Copy_u32PSPval)
{
	UserTasks[CurrenTask].PSPValue=Copy_u32PSPval;
}
void _voidUPdatenextFunction(void)
{
	uint8_t Local_u8TaskCounter;
	for(Local_u8TaskCounter=0;Local_u8TaskCounter < MAX_TASK_NUM;Local_u8TaskCounter++)
	{
		CurrenTask++;
		CurrenTask %=MAX_TASK_NUM;
		if((UserTasks[CurrenTask].CurrentState==Ready_State)&&(CurrenTask!=0U))
		{
			/*cheak if any task is ready excluding the Idle task*/
			break;
		}
	}
	if(UserTasks[CurrenTask].CurrentState !=Ready_State)
	{
		CurrenTask=0;/*All tasks are blocked*/
	}

}
uint32_t _u32GetCurrentPSPValue(void)
{
	return UserTasks[CurrenTask].PSPValue;
}
/**************************************************************************/
__attribute__((naked)) void Stack_voidChangeToPSP(void)
{
	/*1- Init PSP with value of */
	__asm volatile("PUSH {LR}");
	__asm volatile("BL	_u32GetCurrentPSPValue");
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	/*2- change sp to psp using CONTROL register*/
	__asm volatile("MOV R0,#0x02");
	__asm volatile("MSR CONTROL,R0");
	/*return*/
	__asm volatile("BX LR");
}
__attribute__ ((naked)) void Stack_voidGoUnprivileged(void)
{
	/*use psp as stak pointer and go unprivileged*/
	__asm volatile("MOV R0,#0x03");
	__asm volatile("MSR CONTROL,R0");
	/*return*/
	__asm volatile("BX LR");
}
__attribute__ ((naked)) void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedulerTOS)
{
	__asm volatile("MSR MSP,R0");

	/* can use this instead
	 * __asm volatile("MSR MSP ,%0"::"r"(Copy_u32SchedulerTOS));
	 */

	/*return*/
	__asm volatile("BX LR");
}

void STK_voidInit(uint32_t Copy_u32Tickhz)
{
	/*Calculate the requried number of ticks*/
	uint32_t Local_u32ReloadVal= SYSTICK_TIM_CLK/ Copy_u32Tickhz;

	/*Decrement by one to consider the Multi-shot timer*/
	Local_u32ReloadVal--;

	SYSTICK->STK_LOAD=Local_u32ReloadVal;

	/*Enable systick exception*/
	SYSTICK->STK_CTRL |=1<<1;

	/*Set clock source*/
	SYSTICK->STK_CTRL |=1<<2;

	/*Enable the systick timer*/
	SYSTICK->STK_CTRL |=1<<0;
}

__attribute__((naked)) void PendSV_Handler(void)
{
	/*1- Save context of Current task*/
			/*1-Get Current runinng task's PSP value*/
			__asm volatile("MRS R0,PSP");
			/*2-using that psp ,*/
			__asm volatile("STMDB R0!,{R4-R11}");
			/*3-Saave current value of PSP*/
			__asm volatile("PUSH {LR}");
			__asm volatile("BL _void2SavePSPValue");
		/*2- Retrieve context of nsxt task*/
			/*1- Decide the next task to run*/
			__asm volatile("BL _voidUPdatenextFunction");
			/*2-Get its PSP Value*/
			__asm volatile("BL _u32GetCurrentPSPValue");
			__asm volatile("POP {LR}");
			/*3- using the psp value , retrieve SF2(R4-->R11)*/
			__asm volatile("LDM R0!,{R4-R11}");
			/*4- Update PSP Value*/
			__asm volatile("MSR PSP ,R0");
		/*3- return*/
		__asm volatile("BX LR");
}
void UnblockTasks(void)
{
	uint8_t local_u8TaskCounter;
	for (local_u8TaskCounter = 1u; local_u8TaskCounter < MAX_TASK_NUM; ++local_u8TaskCounter)
	{
		if (UserTasks[local_u8TaskCounter].CurrentState==BlockedState)
		{
			if(UserTasks[local_u8TaskCounter].BlockCount == GlobalTickCounter)
			{
				UserTasks[local_u8TaskCounter].CurrentState = Ready_State;
			}
		}
	}
}
void SysTick_Handler(void)
{
	/*1- Update Global Tick Count*/
	GlobalTickCounter++;

	/*2- Unblock Tasks*/
	UnblockTasks();

	/*3- Pend pendSV*/
	SET_PENDSV_PENDING_FLAG;
}
void TaskDelay(uint32_t Copy_u32BlockingCount)
{

	if(CurrenTask != 0U)
	{
		/*Update Task blocking period*/
		UserTasks[CurrenTask].BlockCount = Copy_u32BlockingCount + GlobalTickCounter;

		/*Update Task state*/
		UserTasks[CurrenTask].CurrentState=BlockedState;
		/*Call the scheduler by pending the PendSV*/
		SET_PENDSV_PENDING_FLAG;
	}
}

void IdleTaskHandler(void)
{
	while(1);
}
