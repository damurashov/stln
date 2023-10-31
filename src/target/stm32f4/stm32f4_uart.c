//
// stm32f4_uart.c
//
// Created on: Oct 31, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//
// Implements UART configuration routines

#include "uart.h"
#include "target_stm32f4.h"
#include <stm32f412cx.h>  // Not supposed to matter which platform is used within F4 lineage

/// \brief Initializes UART2
/// \pre Clocking is supposed to be initialized
/// \pre UART2 is supposed to be enabled in CCR
unsigned uartInitialize(int aBaudrate, unsigned aUse9BitWord, unsigned aUse2StopBits)
{
	USART_TypeDef usart;
}
