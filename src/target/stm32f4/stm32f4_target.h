//
// target_stm32f4.h
//
// Created on: Oct 31, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#ifndef TARGET_STM32F4_TARGET_STM32F4_H_
#define TARGET_STM32F4_TARGET_STM32F4_H_

/// Default frequency of HSI clock source
#define TARGET_STM32F4_HSI_FREQUENCY_HZ (16000000)

/// \brief returns UART clock frequency as it is configured in RCC
unsigned long targetStm32f4GetUartClockFrequencyHz();

/// \brief returns clocking frequencies for all (WARN) HW timers
unsigned long targetStm32f4GetTimerClockFrequencyHz();

void targetStm32f4InitializeRng();

void targetStm32F4InitializeTimer();

/// \brief Enables Floating Point Unit
void targetStm32F4EnableFpu();

void targetStm32f4InitializeUart()

#endif // TARGET_STM32F4_TARGET_STM32F4_H_
