//
// uart.h
//
// Created on: Oct 31, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#ifndef COMMON_UART_H_
#define COMMON_UART_H_

enum UartWordLength {
	UartWordLength8Bit = 0,
	UartWordLength9Bit,
};

enum UartStopBitLength {
	UartStopBitLength1 = 0,
	UartStopBitLength1p5,
	UartStopBitLength2,
	UartStopBitLength0p5,
};

/// \brief Performs UART initialization
/// \param `aUartWordLength`: see `UartWordLength`
/// \param `aUartStopBitLength`: see `UartStopBitLength`
void uartInitialize(unsigned long aBaudrate, unsigned aUartWordLength, unsigned aUartStopBitLength);

#endif // COMMON_UART_H_
