/*
 * OSMCAL_interface.h
 *
 *  Created on: Nov 25, 2023
 *      Author: Karim
 */

#ifndef OSMCAL_INTERFACE_H_
#define OSMCAL_INTERFACE_H_
void STK_voidInit(uint32_t Copy_u32Tickhz);
void Stack_voidSchedulerStackInit(uint32_t Copy_u32SchedulerTOS);
void Stack_voidEnableSystenFaultsExcp(void);
void Stack_voidChangeToPSP(void);
void Stack_voidGoUnprivileged(void);
void InitTasksStack(void);
void TaskDelay(uint32_t Copy_u32BlockingCount);
#endif /* OSMCAL_INTERFACE_H_ */
