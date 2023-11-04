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

	return 0;
}

void applicationRun(ApplicationHandle *aApplicationHandle)
{
	(void)aApplicationHandle;
	uartInitialize(ApplicationParameterBaudrate, ApplicationParameterUartWordLength, ApplicationParameterUartStopBits);
	uartSetIsrHook(onUartIsr);
	hwTimerSetIsrHook(onTimerIsr);
	unsigned long randomDelay = randomGetU32FromIsr();
	hwTimerStartTimeoutTicksFromIsr(randomDelay);
}
