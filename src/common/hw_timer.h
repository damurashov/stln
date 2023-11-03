//
// hw_timer.h
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (d <DOT> murashov <AT> geoscan <DOT> aero)
//

#ifndef COMMON_HW_TIMER_H_
#define COMMON_HW_TIMER_H_

/// Will be invoked each time the timer's interrupt gets triggered
typedef void (*HwTimerIsrHook)();

/// \brief Initializes timer w/ `HwTimerIsrHook` instance
/// \pre The timer must be pre-initialized for a target
void hwTimerSetIsrHook(HwTimerIsrHook aHwTimerIsrHook);

/// \brief after # `anTicks` the `HwTimerIsrHook` will get triggered (if one
/// will have been set by the time)
/// \details May be called from either ISR, or thread mode
void hwTimerStartTimeoutTicksFromIsr(unsigned long anTicks);

#endif // COMMON_HW_TIMER_H_
