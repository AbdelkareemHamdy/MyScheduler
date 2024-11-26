/*
 * @GPIO_program.c
 * @Author Abdelkareem Hamdy
 * @brief The GPIO main source file, including functions` definitions
 *  Created on: May 6, 2023
 *      Author: kareem
 */
#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"

#include "GPIO_interface.h"
#include "GPIO_prv.h"


#include"GPIO_interface.h"
static GPIO_RegDef_t* GPIO_PORT[GPIO_PERIPHERSL_NUM]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOE,GPIOF,GPIOG,GPIOH};
/****************************************************
 * @fn GPIO_u8PinInit
 * @brief the function initializes the GPIO pin according to the input parameters
 * @param[in] PinConfig : the initialization values of the pin
 * @retval Error Status
 */
uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t* PinConfig)
{
	uint8_t Local_u8ErrorState = OK;
	if(PinConfig!=NULL)
	{
		if(((PinConfig->port) <= PORTH)&&((PinConfig->pin)<=PIN15))
		{
			/*Slect GPIO modes : Input , Output , */
			(GPIO_PORT[PinConfig->port]->GPIO_MODER) &=~(MODER_MASK       <<((PinConfig->pin) * MODE_PIN_ACCESS)); /*Clear the mode bits */
			(GPIO_PORT[PinConfig->port]->GPIO_MODER) |=((PinConfig->mode) <<((PinConfig->pin) * MODE_PIN_ACCESS));
			/*Slect GPIO modes : NoPull , PullUp or PullDown */
			(GPIO_PORT[PinConfig->port]->GPIO_PUPDR) &=~(PUPDR_MASK            <<((PinConfig->pin) * PUPDR_PIN_ACCESS));
			(GPIO_PORT[PinConfig->port]->GPIO_PUPDR) |=((PinConfig->PullType) <<((PinConfig->pin) * PUPDR_PIN_ACCESS));
			/*Slect Output Type & Output speed in case of General purpose output or Alternate function */
			if(((PinConfig->mode)==OUTPUT)||((PinConfig->mode)==ALTERNATE_FUNCTION))
			{
				/*Slect Output type : Push Pull or Open drain*/
				(GPIO_PORT[PinConfig->port]->GPIO_OTYPER) &=~(OTYPER_MASK         	<<(PinConfig->pin)); //bit masking
				(GPIO_PORT[PinConfig->port]->GPIO_OTYPER) |=((PinConfig->PullType) 	<<(PinConfig->pin));
				/*Slect Output speed : Low, Medium, Fast or High*/
				(GPIO_PORT[PinConfig->port]->GPIO_OSPEEDR) &=~(OSPEEDR_MASK             <<((PinConfig->pin) *OSPEEDR_PIN_ACCESS));
				(GPIO_PORT[PinConfig->port]->GPIO_OSPEEDR) |=((PinConfig->speed)		   <<((PinConfig->pin) *OSPEEDR_PIN_ACCESS));

				/*Slect the pin Alternate function*/
				if((PinConfig->mode)==ALTERNATE_FUNCTION)
				{
					uint8_t Local_u8RegNum = (PinConfig->pin) /AFR_PIN_SHIFTING;
					uint8_t Local_u8BitNum = (PinConfig->pin) %AFR_PIN_SHIFTING;

					(GPIO_PORT[PinConfig->port]->GPIO_AFR[Local_u8RegNum]) &=~(AFR_MASK            <<(Local_u8BitNum*AFR_PIN_ACCESS));
					(GPIO_PORT[PinConfig->port]->GPIO_AFR[Local_u8RegNum]) |=((PinConfig->AltFunc) <<(Local_u8BitNum*AFR_PIN_ACCESS));
				}
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return  Local_u8ErrorState ;
}
/****************************************************
 * @fn GPIO_u8SetPinValue
 * @brief the function initializes the GPIO pin according to the input parameters
 * @param[in] Port : the port number ,get options port  @
 * @param[in] PinNumber : the initialization values of the pin
 * @param[in] PinVal : the initialization values of the pin
 *
 * @retval Error Status
 */
uint8_t GPIO_u8SetPinValue(Port_t Port,Pin_t PinNumber,PinVal_t PinVal)
{
	uint8_t Local_u8ErrorState = OK;
	if((Port <= PORTH)&&(PinNumber<=PIN15))
	{
		if (PIN_LOW==PinVal)
		{
			(GPIO_PORT[Port]->GPIO_BSRR) = (ONE_BIT_MASK << (PinNumber+16));
		}
		else if (PIN_HIGH==PinVal)
		{
			(GPIO_PORT[Port]->GPIO_BSRR) = (ONE_BIT_MASK << PinNumber);
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;

}
uint8_t GPIO_u8TogglePinValue(Port_t Port,Pin_t PinNumber)
{
	uint8_t Local_u8ErrorState = OK;
	if((Port <= PORTH)&&(PinNumber<=PIN15))
	{
		(GPIO_PORT[Port]->GPIO_ODR) ^=(ONE_BIT_MASK << PinNumber);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t GPIO_u8GetPinValue(Port_t Port,Pin_t PinNumber,PinVal_t* PinVal)
{
	uint8_t Local_u8ErrorState = OK;
	if((Port <= PORTH)&&(PinNumber<=PIN15))
	{
		*PinVal = (ONE_BIT_MASK & ((GPIO_PORT[Port]->GPIO_IDR) >> PinNumber));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
