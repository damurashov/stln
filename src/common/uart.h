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

/// \param `aNextChar` -- the next UART character
/// \returns 1, if the next character is valid (the buffer was not empty). 0
/// otherwise
typedef int (*UartIsrHook)(unsigned char *aOutNextChar);

/// \brief Performs UART initialization
/// \param `aUartWordLength`: see `UartWordLength`
/// \param `aUartStopBitLength`: see `UartStopBitLength`
void uartInitialize(unsigned long aBaudrate, unsigned aUartWordLength, unsigned aUartStopBitLength);

/// \brief Initializes static UART ISR hook
void uartSetIsrHook(UartIsrHook aUartIsrHook);

/// \brief Enables UART transmission. May be called from either exception or
/// threading mode
void uartEnableFromIsr();

/// \brief Disables UART transmissions. May be called from either exception or
/// threading mode
void uartDisableFromIsr();

#endif // COMMON_UART_H_
