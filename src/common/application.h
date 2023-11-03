//
// application.h
//
// Created on: Nov 03, 2023
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL> <DOT> <COM>)
//

#ifndef COMMON_APPLICATION_H_
#define COMMON_APPLICATION_H_

typedef void *ApplicationHandle;

void *applicationInitialize();
void applicationRun(ApplicationHandle *aApplicationHandle);

#endif // COMMON_APPLICATION_H
