//
// stm32f4_uart.c
//
// Created on: Oct 31, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//
// Implements UART configuration routines

#include "stm32f4_target.h"
#include "uart.h"
#include <stm32f412cx.h>  // Not supposed to matter which platform is used within F4 lineage

static UartIsrHook sUartIsrHook = 0;
static USART_TypeDef *sUsartRegisters = USART2;

/// \brief Overrides `stm32f412_startup.s`
void gUsart2Isr()
{
	USART_TypeDef *usart = sUsartRegisters;
	unsigned char nextCharacter;

	if (sUartIsrHook != 0 && sUartIsrHook(&nextCharacter)) {
		usart->DR = nextCharacter;
	} else {
		uartDisableFromIsr();
	}
}

/// \brief Initializes UART2
/// \pre Clocking is supposed to be initialized
/// \pre UART2 is supposed to be enabled in CCR
void uartInitialize(unsigned long aBaudrate, unsigned aUartWordLength, unsigned aUartStopBitLength)
{
	volatile USART_TypeDef *usart = sUsartRegisters;
	usart->CR1 |= USART_CR1_TXEIE;  // Enable "TX empty" interrupt

	// Configure word length
	if (aUartWordLength == UartWordLength9Bit) {
		usart->CR1 |= USART_CR1_M;
	}

	// Configure the number of stop bits
	switch (aUartStopBitLength) {
		case UartStopBitLength0p5:  // See RM0402, Rev. 6, p. 806
			usart->CR2 |= USART_CR2_STOP_0;

			break;

		case UartStopBitLength1:
			break;

		case UartStopBitLength1p5:
			usart->CR2 |= (USART_CR2_STOP_0 | USART_CR2_STOP_1);

			break;

		case UartStopBitLength2:
			usart->CR2 |= USART_CR2_STOP_1;

			break;
	}

	// Configure fractional baudate value, RM0402, Rev. 6, p. 772
	{
		const int useOversampling8 = 0; // TODO: optimize out, use defines
		const float usartDivf = ((float)targetStm32f4GetUartClockFrequencyHz())
			/ (8 * (2 - useOversampling8) * aBaudrate);
		const unsigned long mantissa = (unsigned long)usartDivf;
		const float fractionCoefficientMultiplierf = 16.0f;
		const unsigned long long fraction = (unsigned long long)(fractionCoefficientMultiplierf
			* (usartDivf - (float)mantissa));
		usart->BRR = (mantissa << 4) | fraction;
	}
}

void uartSetIsrHook(UartIsrHook aUartIsrHook)
{
	sUartIsrHook = aUartIsrHook;
}

void uartEnableFromIsr()
{
	volatile USART_TypeDef *usart = sUsartRegisters;
	usart->CR1 |= USART_CR1_TXEIE  // Enable transmission
		| USART_CR1_TE;  // Enable usart interrupt on empty transmission buffer
}

void uartDisableFromIsr()
{
	volatile USART_TypeDef *usart = sUsartRegisters;
	usart->CR1 &= ~(USART_CR1_TXEIE  // Enable transmission
		| USART_CR1_TE);  // Enable usart interrupt on empty transmission buffer
}
