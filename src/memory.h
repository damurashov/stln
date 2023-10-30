//
// memory.h
//
// Created on: 2023-10-30
//     Author: Dmitry Murashov (dmtr <DOT> murashov <AT> <GMAIL>)
//
// Module that is responsible for various memory-related functions such as
// memory sections initialization
//

/// @brief Initializes .bss section
void memoryInitializeBss();

/// @brief Initializes .data section
void memoryInitializeData();
