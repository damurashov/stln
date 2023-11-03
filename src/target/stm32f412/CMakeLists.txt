# Specify source files
file(GLOB SOURCES "./*.c" "./*.s")

# Build the library
add_library(stm32f412 STATIC ${SOURCES})

# Set linker script
get_filename_component(LINKER_SCRIPT_PATH "./stm32f412.ld" REALPATH)
set_property(GLOBAL PROPERTY LINKER_SCRIPT_PATH ${LINKER_SCRIPT_PATH})

if (USE_STM32CUBEF4_LIBRARY)
	target_link_libraries(stm32f412 PRIVATE stm32cubef4 stm32f4)
endif()
