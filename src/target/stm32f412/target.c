//
// target.c
//
// Created on: Oct 30, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//
// Implements "target.h" API

#include <stm32f412cx.h>

void targetInitializeClock()
{
	// Enable HSI clock source
	RCC->CR |= RCC_CR_HSION;

	// Busy-wait until HSI is ready
	while (!(RCC->CR & RCC_CR_HSIRDY)) {
	}

	// Use HSI as the system clock source
	RCC->CFGR |= RCC_CFGR_SW_HSI;

	// Enable peripherals on AHB1
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIO A (USART 2)
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
}
