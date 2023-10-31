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
/// \param `aUse9BitWord`: see `UartWordLength`
/// \param `aUse9BitWord`: see `UartStopBitLength`
unsigned uartInitialize(int aBaudrate, unsigned aUse9BitWord, unsigned aUse2StopBits);

#endif // COMMON_UART_H_
