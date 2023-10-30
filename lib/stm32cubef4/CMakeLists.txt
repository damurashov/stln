add_library(stm32cubef4 INTERFACE)

target_include_directories(stm32cubef4 INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/stm32cubef4/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
	"${CMAKE_CURRENT_SOURCE_DIR}/stm32cubef4/Drivers/CMSIS/Core/Include"
)
