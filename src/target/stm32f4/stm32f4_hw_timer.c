//
// stm32f4_timer.c
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#include "hw_timer.h"
#include "stm32f4_hw_timer.h"
#include "stm32f4_target.h"

static HwTimerIsrHook sHwTimerIsrHook;

void tim2Isr()
{
	volatile TIM_TypeDef *tim = stm32f4TimerGetTimTypedef();
	tim->CR1 &= ~(TIM_CR1_CEN);  // Disable timer
	tim->SR = 0;  // Reset interrupt flags (UIF, in particular)

	if (sHwTimerIsrHook != 0) {
		unsigned long nextTimeoutTicks = sHwTimerIsrHook();

		if (nextTimeoutTicks > 0) {
			hwTimerStartTimeoutTicksFromIsr(nextTimeoutTicks);
		}
	}
}

void hwTimerSetIsrHook(HwTimerIsrHook aHwTimerIsrHook)
{
	sHwTimerIsrHook = aHwTimerIsrHook;
}

void hwTimerStartTimeoutTicksFromIsr(unsigned long aNextTimeoutTicks)
{
	volatile TIM_TypeDef *tim = stm32f4TimerGetTimTypedef();
	tim->ARR = aNextTimeoutTicks;
	tim->CNT = aNextTimeoutTicks;  // The CNT is reloaded w/ ARR on TIMx UI, but it is unclear whether it happens before, or after UI. Ensure consistency
	tim->CR1 |= TIM_CR1_CEN;  // Enable timer
}

unsigned long hwTimerGetCounterFrequency()
{
	return targetStm32f4GetTimerClockFrequencyHz();  // The timer's prescaler was not set
}
