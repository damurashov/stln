//
// stm32f4_random.c
//
// Created on: Nov 02, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//
// Implements common/random.h

#include <stm32f412cx.h>

unsigned long randomGetU32FromIsr()
{
	return RNG->DR;  // RM0402 Rev 6 p. 411
}
