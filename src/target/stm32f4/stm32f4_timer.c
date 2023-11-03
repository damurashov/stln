//
// stm32f4_timer.c
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#include "hw_timer.h"
#include "stm32f4_timer.h"

static HwTimerIsrHook sHwTimerIsrHook;

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
