# Specify source files
file(GLOB SOURCES "./*.c" "./*.s")

# Build the library
add_library(stm32f407ig STATIC ${SOURCES})

# Set linker script
get_filename_component(LINKER_SCRIPT_PATH "./stm32f407ig.ld" REALPATH)
stap_build_configuration_append_linker_flag("-Wl,-T${LINKER_SCRIPT_PATH}")
stap_build_configuration_apply_flags_to_target(stm32f407ig)

if (USE_STM32CUBEF4_LIBRARY)
	target_link_libraries(stm32f407ig PRIVATE stm32cubef4 stm32f4)
endif()
