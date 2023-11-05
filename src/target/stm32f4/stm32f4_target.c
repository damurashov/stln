//
// target.c
//
// Created on: Oct 30, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//
// Implements "target.h" API

#include "stm32f4_hw_timer.h"
#include "stm32f4_target.h"
#include "stm32f4_uart.h"
#include <stm32f412cx.h>

#define PLLM_SOURCE_FREQUENCY (TARGET_STM32F4_HSI_FREQUENCY_HZ)
#define PLLM_FREQUENCY_DIVISION_FACTOR (2)

#if PLLM_FREQUENCY_DIVISION_FACTOR != 2
#error Unsupported configuration
#endif  /* PLLM_FREQUENCY_DIVISION_FACTOR */

#define CPACR ((unsigned long *)0xE000ED88)
#define CPACR_CP10_FULL_ACCESS (0x3 << 20)
#define CPACR_CP11_FULL_ACCESS (0x3 << 22)

#define TIM2_PRIORITY (50)
#define USART1_PRIORITY (50)

#if TIM2_PRIORITY != USART1_PRIORITY
#error Misconfiguration detected: TIM2 and USART1 priorities must be equal to enable daisy-chaining and thus ensure mutual exclusion while working with a circular buffer. See also "application.c".
#endif

unsigned long targetStm32f4GetUartClockFrequencyHz()
{
	// A direct clock from HSI was used
	return TARGET_STM32F4_HSI_FREQUENCY_HZ;
}

void targetStm32f4InitializeRng()
{
	volatile RNG_TypeDef *rng = RNG;

	// Enable RNG
	rng->CR |= RNG_CR_RNGEN;  // enable
}

void targetStm32f4InitializeClock()
{
	// Enable HSI clock source
	volatile RCC_TypeDef *rcc = RCC;
	rcc->CR |= RCC_CR_HSION  // Enable HSI
		| RCC_CR_PLLON;  // Enable PLL (for RNG)

	// Busy-wait until HSI and PLL are ready
	while (!((rcc->CR & RCC_CR_HSIRDY) && (rcc->CR & RCC_CR_PLLRDY))) {
	}

	// Use HSI as the system clock source
	rcc->CFGR |= RCC_CFGR_SW_HSI;

	// Enable peripherals
	rcc->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIO A (USART 2)
	rcc->AHB2ENR |= RCC_AHB2ENR_RNGEN;  // Enable random number generator
	rcc->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable TIM 2
}

void targetStm32F4InitializeTimer()
{
	volatile TIM_TypeDef *tim = stm32f4TimerGetTimTypedef();
	tim->CR1 |= TIM_CR1_DIR  // Use as downcounter
		| TIM_CR1_ARPE;  // Enable auto-reload preload
	tim->DIER |= TIM_DIER_UIE;  // Enable TIM2 update interrupt
}

void targetStm32F4EnableFpu()
{
	volatile unsigned long *cpacr = CPACR;
	*cpacr |= (CPACR_CP10_FULL_ACCESS | CPACR_CP11_FULL_ACCESS);
}

unsigned long targetStm32f4GetTimerClockFrequencyHz()
{
	return TARGET_STM32F4_HSI_FREQUENCY_HZ;  // Timers are clocked directly from HSI, no downstream APB1 prescalers were used
}

void targetStm32f4InitializeUart()
{
	volatile RCC_TypeDef *rcc = RCC;
	volatile USART_TypeDef *usart = stm32f4UartGetTypeDef();
	volatile GPIO_TypeDef *gpio = GPIOA;

	rcc->APB2ENR |= RCC_APB2ENR_USART1EN;  // Enable USART 1
	usart->CR1 |= USART_CR1_UE;

	// Initialize USART-related GPIOs
	gpio->MODER |= GPIO_MODER_MODE9_1;  // PA9, AF mode
	gpio->PUPDR |= GPIO_PUPDR_PUPD9_0;  // PA9, pull-up
	gpio->AFR[1] |= (7 << 4);  // PA9, AF7
}

void targetUp()
{
	targetStm32F4EnableFpu();
	targetStm32f4InitializeClock();
	targetStm32f4InitializeUart();
	targetStm32f4InitializeRng();
	targetStm32F4InitializeTimer();
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, USART1_PRIORITY);
	NVIC_SetPriority(TIM2_IRQn, TIM2_PRIORITY);
}
