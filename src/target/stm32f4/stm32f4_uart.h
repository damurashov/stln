//
// stm32f4_uart.h
//
// Created on: Nov 05, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//

#ifndef TARGET_STM32F4_STM32F4_UART_H_
#define TARGET_STM32F4_STM32F4_UART_H_

#include <stm32f412cx.h>

static inline USART_TypeDef *stm32f4UartGetTypeDef()
{
	return USART2;
}

#endif // TARGET_STM32F4_STM32F4_UART_H_

