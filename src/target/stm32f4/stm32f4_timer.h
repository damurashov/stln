//
// stm32f4_timer.h
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#ifndef TARGET_STM32F4_STM32F4_TIMER_H_
#define TARGET_STM32F4_STM32F4_TIMER_H_

#include <stm32f412cx.h>

/// \brief Defines the timer being used
static inline TIM_TypeDef *stm32f4TimerGetTimTypedef()
{
	return TIM2;
}

#endif // TARGET_STM32F4_STM32F4_TIMER_H_
