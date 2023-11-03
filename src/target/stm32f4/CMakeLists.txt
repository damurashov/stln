file(GLOB SOURCES "*.c")
add_library(stm32f4 ${SOURCES})
target_include_directories(stm32f4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_INCLUDE_DIRECTORIES})
target_link_libraries(stm32f4 PUBLIC stm32cubef4)


# Specify linker options
get_property(LINKER_SCRIPT GLOBAL PROPERTY LINKER_SCRIPT_PATH)
string(JOIN " " LINKER_OPTIONS
	"-T${LINKER_SCRIPT}"
	"-ffreestanding"  # Imply there is no operating system, or standard library on the target platform
	"-nostartfiles"  # Do not run startup operations, such as setting global variables to their initial values. Do not use default startup files.
	"-ffunction-sections"  # Place each function into its own linker section to enable better optimization
	"-fdata-sections"
)

# Specify compiler options
string(JOIN " " COMPILER_OPTIONS
	"-mthumb"  # Use thumb code
	"-mcpu=cortex-m4"  # Specify CPU architecture
)

if (${BUILD_TYPE} STREQUAL "Debug")
	string(JOIN " " COMPILER_OPTIONS
		${COMPILER_OPTIONS}
		"-g3"
	)
endif()

# Apply linker and compiler options
message(STATUS "Using linker options: `${LINKER_OPTIONS}`")
target_link_options(stm32f4 PUBLIC "SHELL:${LINKER_OPTIONS}")
message(STATUS "Using compiler options: `${COMPILER_OPTIONS}`")
target_compile_options(stm32f4 PUBLIC "SHELL:${COMPILER_OPTIONS}")
set_target_properties(stm32f4 PROPERTIES LINKER_LANGUAGE C)
target_include_directories(stm32f4 PUBLIC ${COMMON_INCLUDE_DIRECTORIES})
