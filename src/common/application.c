//
// application.c
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//

#include "hw_timer.h"
#include "random.h"
#include "ring_buffer.h"
#include "uart.h"

#include "application.h"

enum ApplicationParameter {
	ApplicationParameterBaudrate = 115200,
	ApplicationParameterUartWordLength = UartWordLength8Bit,
	ApplicationParameterUartStopBits = UartStopBitLength1,
	ApplicationParameterMaxTimerDelayMs = 1000U,
};

struct {
	RingBuffer ringBuffer;
} sApplication;

static int onUartIsr(unsigned char *aNextChar);
static unsigned long onTimerIsr();

static int onUartIsr(unsigned char *aNextChar)
{
	return ringBufferTryGetc(&sApplication.ringBuffer, aNextChar);
}

static unsigned long onTimerIsr()
{
	const unsigned char nextChar = (unsigned char)randomGetU32FromIsr();
	unsigned long nextTimeout = randomGetU32FromIsr();
	const unsigned long timerCounterFrequency = hwTimerGetCounterFrequency();
	const unsigned long timerTickValueUpperBound = timerCounterFrequency / 1000U * ApplicationParameterMaxTimerDelayMs;

	// Scale next timeout, so we won't have to wait for too long
	nextTimeout %= timerTickValueUpperBound;

	// Ensure the stream never stops
	if (nextTimeout == 0U) {
		nextTimeout = 1U;
	}

	ringBufferPutc(&sApplication.ringBuffer, nextChar);
	uartEnableFromIsr();  // UART may be disabled in the case of an empty buffer

	return nextTimeout;
}

ApplicationHandle applicationInitialize()
{
	ringBufferInitialize(&sApplication.ringBuffer);
	uartInitialize(ApplicationParameterBaudrate, ApplicationParameterUartWordLength, ApplicationParameterUartStopBits);
	uartSetIsrHook(onUartIsr);
	hwTimerSetIsrHook(onTimerIsr);

	return 0;
}

void applicationRun(ApplicationHandle *aApplicationHandle)
{
	(void)aApplicationHandle;
	hwTimerStartTimeoutTicksFromIsr(42);  // Initial boot
}
