//
// target.c
//
// Created on: Oct 30, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//
// Implements "target.h" API

#include "target_stm32f4.h"
#include <stm32f412cx.h>

unsigned long long targetStm32f4GetUartClockFrequencyHz()
{
	// A direct clock from HSI was used
	return TARGET_STM32F4_HSI_FREQUENCY_HZ;
}

void targetInitializeClock()
{
	// Enable HSI clock source
	volatile RCC_TypeDef *rcc = RCC;
	rcc->CR |= RCC_CR_HSION;

	// Busy-wait until HSI is ready
	while (!(rcc->CR & RCC_CR_HSIRDY)) {
	}

	// Use HSI as the system clock source
	rcc->CFGR |= RCC_CFGR_SW_HSI;

	// Enable peripherals
	rcc->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIO A (USART 2)
	rcc->AHB2ENR |= RCC_AHB2ENR_RNGEN;  // Enable random number generator
	rcc->APB1ENR |= RCC_APB1ENR_USART2EN  // Enable USART 2
		| RCC_APB1ENR_TIM2EN;  // Enable TIM 2
}
