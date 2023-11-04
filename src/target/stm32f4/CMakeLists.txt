file(GLOB SOURCES "*.c")
add_library(stm32f4 ${SOURCES})
target_include_directories(stm32f4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_INCLUDE_DIRECTORIES})
target_link_libraries(stm32f4 PUBLIC stm32cubef4)

stap_build_configuration_append_linker_flag("-ffunction-sections")  # Place each function into its own linker section to enable better optimization
stap_build_configuration_append_linker_flag("-fdata-sections")
stap_build_configuration_append_linker_flag("-nostartfiles")  # Do not run startup operations, such as setting global variables to their initial values. Do not use default startup files.
stap_build_configuration_append_linker_flag("-ffreestanding")  # Imply there is no operating system, or standard library on the target platform
stap_build_configuration_append_cflag("-mthumb")  # Use thumb code
stap_build_configuration_append_cflag("-mcpu=cortex-m4")  # Specify CPU architecture
stap_build_configuration_append_cflag("-mlittle-endian")
stap_build_configuration_append_cflag("-mfloat-abi=hard")  # The target features FP hardware
stap_build_configuration_append_cflag("-ffreestanding")  # Imply there is no operating system, or standard library on the target platform
stap_build_configuration_append_cflag("-nostartfiles")  # Do not run startup operations, such as setting global variables to their initial values. Do not use default startup files.
stap_build_configuration_append_asmflag("-mthumb")  # Use thumb code
stap_build_configuration_append_asmflag("-mcpu=cortex-m4")  # Specify CPU architecture
stap_build_configuration_append_asmflag("-mlittle-endian")
#stap_build_configuration_append_asmflag("-mfloat-abi=hard")  # The target features FP hardware
stap_build_configuration_apply_flags_to_target(stm32f4)

if (${BUILD_TYPE} STREQUAL "Debug")
	stap_build_configuration_append_cflag("-g3")  # The target features FP hardware
endif()

target_include_directories(stm32f4 PUBLIC ${COMMON_INCLUDE_DIRECTORIES})
