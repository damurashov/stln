//
// stm32f4_timer.c
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#include "hw_timer.h"
#include "stm32f4_hw_timer.h"

static HwTimerIsrHook sHwTimerIsrHook;

void tim2Isr()
{
	volatile TIM_TypeDef *tim = stm32f4TimerGetTimTypedef();
	tim->CR1 &= ~(TIM_CR1_CEN);  // Disable timer
	tim->SR = 0;  // Reset interrupt flags (UIF, in particular)

	if (sHwTimerIsrHook != 0) {
		unsigned long nextTimeoutTicks = sHwTimerIsrHook();

		if (nextTimeoutTicks > 0) {
			tim->ARR = nextTimeoutTicks;
			tim->CR1 |= TIM_CR1_CEN;  // Enable timer
		}
	}
}

void hwTimerSetIsrHook(HwTimerIsrHook aHwTimerIsrHook)
{
	sHwTimerIsrHook = aHwTimerIsrHook;
}

void hwTimerStartTimeoutTicksFromIsr(unsigned long anTicks)
{
	volatile TIM_TypeDef *tim = stm32f4TimerGetTimTypedef();
	tim->ARR = anTicks;  // Set the number of ticks
	tim->CR1 |= TIM_CR1_CEN;  // Enable counting
}
