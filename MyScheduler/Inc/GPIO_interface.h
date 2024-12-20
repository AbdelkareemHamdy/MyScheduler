#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
}Port_t;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}Pin_t;

typedef enum
{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
}Mode_t;	
typedef enum
{
	SPEED_LOW=0,
	SPEED_MEDIUM,
	SPEED_FASR,
	SPEED_HIGH
}OutputSpeed_t;

typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}OutputType_t;

typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AltFunc_t;

typedef enum
{
	NOPULL=0,
	PULLUP,
	PULLDOWN
}PullUpDown_t;

typedef enum
{
	PIN_LOW=0,
	PIN_HIGH
}PinVal_t;
typedef struct
{
	Port_t port;
	Pin_t pin;
	Mode_t mode;
	OutputSpeed_t speed;
	OutputType_t OutputType;
	PullUpDown_t PullType;
	AltFunc_t AltFunc;
}GPIO_PinConfig_t;

uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t* PinConfig);
uint8_t GPIO_u8SetPinValue(Port_t Port,Pin_t PinNumber,PinVal_t PinVal);
uint8_t GPIO_u8TogglePinValue(Port_t Port,Pin_t PinNumber);
uint8_t GPIO_u8GetPinValue(Port_t Port,Pin_t PinNumber,PinVal_t* PinVal);

#endif
