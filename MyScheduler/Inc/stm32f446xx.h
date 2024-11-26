#ifndef STM32F446XX_H
#define STM32F446XX_H
/******************** Various Memories Base Addresses *****************/
#define FLASH_BASE_ADDRESS		0X08000000UL
#define SRAM_BASE_ADDRESS		  0X20000000UL
#define ROM_BASE_ADDRESS		  0X1FFF0000UL

/******************** Core peripherals Base Addresses *****************/
#define NVIC_BASE_ADDRESS		  0XE000E100UL
#define SYSTICK_BASE_ADDRESS	0xE000E010UL
#define SCB_BASE_ADDRESS      0xE000E008UL

/******************** AHB1 Peripheral Base Addresses *****************/
#define GPIOA_BASE_ADDRESS		0x40020000UL
#define GPIOB_BASE_ADDRESS		0x40020400UL
#define GPIOC_BASE_ADDRESS		0x40020800UL
#define GPIOD_BASE_ADDRESS		0x40020C00UL
#define GPIOE_BASE_ADDRESS		0x40021000UL
#define GPIOF_BASE_ADDRESS		0x40021400UL
#define GPIOG_BASE_ADDRESS		0x40021800UL
#define GPIOH_BASE_ADDRESS		0x40021C00UL
					
#define RCC_BASE_ADDRESS		  0x40023800UL


/******************** AHB2 Peripheral Base Addresses *****************/

/******************** AHB3 Peripheral Base Addresses *****************/


/******************** APB1 Peripheral Base Addresses *****************/


/******************** APB2 Peripheral Base Addresses *****************/
#define EXTI_BASE_ADDRESS		    0x40013C00UL
#define SYSCFG_BASE_ADDRESS		  0x40013800UL
/******************** EXTI Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
}EXTI_RegDef_t;
/******************** SYSCFG Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
  volatile uint32_t Reserved1[2];
	volatile uint32_t SYSCFG_CMPCR;
  volatile uint32_t Reserved2[2];
	volatile uint32_t SYSCFG_CFGR;
}SYSCFG_RegDef_t;

/******************** NVIC Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t NVIC_ISER[8];
  volatile uint32_t Reserved2[24];
  volatile uint32_t NVIC_ICER[8];
  volatile uint32_t Reserved3[24];
  volatile uint32_t NVIC_ISPR[8];
  volatile uint32_t Reserved4[24];
  volatile uint32_t NVIC_ICPR[8];
  volatile uint32_t Reserved5[24];
  volatile uint32_t NVIC_IABR[8];
  volatile uint32_t Reserved6[56];
  volatile uint8_t NVIC_IPR[240];
  volatile uint32_t Reserved7[244];
  volatile uint32_t NVIC_STIR;
}NVIC_RegDef_t;
/******************** SCB Register Definition Structure *****************/
typedef struct
{
  volatile uint32_t SCB_ACTLR;
  volatile uint32_t Reserved1[829];
	volatile uint32_t SCB_CPUID;
  volatile uint32_t SCB_ICSR;
  volatile uint32_t SCB_VTOR;
  volatile uint32_t SCB_AIRCR;
  volatile uint32_t SCB_SCR;
  volatile uint32_t SCB_CCR;
  volatile uint8_t SCB_SHPR[12];
  volatile uint32_t SCB_SHCSR;
  volatile uint32_t SCB_CFSR;
  volatile uint32_t SCB_HFSR;
  volatile uint32_t Reserved2;
  volatile uint32_t SCB_MMAR;
  volatile uint32_t SCB_BFAR;
  volatile uint32_t SCB_AFSR;
}SCB_RegDef_t;
/******************** SYSTICK Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t STK_CTRL;
	volatile uint32_t STK_LOAD;
	volatile uint32_t STK_VAL;
	volatile uint32_t STK_CALIB;
}SYSTICK_RegDef_t;
/******************** RCC Register Definition Structure *****************/
typedef struct
{
  volatile uint32_t RCC_CR;            /*!< RCC clock control register,                                   */
  volatile uint32_t RCC_PLLCFGR;       /*!< RCC PLL configuration register,                               */
  volatile uint32_t RCC_CFGR;          /*!< RCC clock configuration register,                             */
  volatile uint32_t RCC_CIR;           /*!< RCC clock interrupt register,                                 */
  volatile uint32_t RCC_AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                           */
  volatile uint32_t RCC_AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                           */
  volatile uint32_t RCC_AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                           */
  uint32_t      RESERVED0;     		/*!< Reserved, 0x1C                                                */
  volatile uint32_t RCC_APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32_t RCC_APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           */
  uint32_t      RESERVED1[2];  		/*!< Reserved, 0x28-0x2C                                           */
  volatile uint32_t RCC_AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                           */
  volatile uint32_t RCC_AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                           */
  volatile uint32_t RCC_AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                           */
  uint32_t      RESERVED2;     		/*!< Reserved, 0x3C                                                */
  volatile uint32_t RCC_APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32_t RCC_APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    */
  uint32_t      RESERVED3[2];  		/*!< Reserved, 0x48-0x4C                                           */
  volatile uint32_t RCC_AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED4;     		/*!< Reserved, 0x5C                                                */
  volatile uint32_t RCC_APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED5[2];  		/*!< Reserved, 0x68-0x6C                                           */
  volatile uint32_t RCC_BDCR;          /*!< RCC Backup domain control register,                           */
  volatile uint32_t RCC_CSR;           /*!< RCC clock control & status register,                          */
  uint32_t      RESERVED6[2];  		/*!< Reserved, 0x78-0x7C                                           */
  volatile uint32_t RCC_SSCGR;         /*!< RCC spread spectrum clock generation register,                */
  volatile uint32_t RCC_PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                            */
  volatile uint32_t RCC_PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                            */
  volatile uint32_t RCC_DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                  */
  volatile uint32_t RCC_CKGATENR;      /*!< RCC Clocks Gated ENable Register,                             */
  volatile uint32_t RCC_DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,                */
}RCC_RegDef_t;
/******************** GPIO Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t GPIO_MODER;
	volatile uint32_t GPIO_OTYPER;
	volatile uint32_t GPIO_OSPEEDR;
	volatile uint32_t GPIO_PUPDR;
	volatile uint32_t GPIO_IDR;
  volatile uint32_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	volatile uint32_t GPIO_LCKR;
	volatile uint32_t GPIO_AFR[2];
}GPIO_RegDef_t;

/******************** GPIO Peripheral Definition *****************/

#define GPIOA	((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB	((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC	((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD	((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE	((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF	((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG	((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH	((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

/******************** RCC Peripheral Definition *****************/

#define RCC	((RCC_RegDef_t*)RCC_BASE_ADDRESS)

/******************** SYSTICK Peripheral Definition *****************/
#define SYSTICK	((SYSTICK_RegDef_t*)SYSTICK_BASE_ADDRESS)

/******************** NVIC Peripheral Definition *****************/
#define NVIC	((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)

/******************** SCB Peripheral Definition *****************/
#define SCB	((SCB_RegDef_t*)SCB_BASE_ADDRESS)

/******************** EXTI Peripheral Definition *****************/
#define EXTI	((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)

/******************** EXTI Peripheral Definition *****************/
#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)


#endif