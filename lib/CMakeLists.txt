set(USE_STM32CUBEF4_LIBRARY ON)

if (USE_STM32CUBEF4_LIBRARY)
	add_subdirectory(stm32cubef4)
	message(STATUS "Using library stm32cubef4")
endif()

