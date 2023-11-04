# Sets common linker / compiler flags

set_property(GLOBAL PROPERTY STAP_CFLAGS ${LINKER_SCRIPT_PATH})
set_property(GLOBAL PROPERTY STAP_ASMFLAGS ${LINKER_SCRIPT_PATH})
set_property(GLOBAL PROPERTY STAP_LINKER_FLAGS ${LINKER_SCRIPT_PATH})
set_property(GLOBAL PROPERTY STAP_TARGETS "")

# Updates the global list of C flags
macro(stap_build_configuration_append_cflag CFLAG)
	message(STATUS "Adding CFLAG ${CFLAG}")
	get_property(_TEMP GLOBAL PROPERTY STAP_CFLAGS)
	list(APPEND _TEMP ${CFLAG})
	set_property(GLOBAL PROPERTY STAP_CFLAGS ${_TEMP})
endmacro()

# Updates the global list of ASM flags
macro(stap_build_configuration_append_asmflag asmflag)
	message(STATUS "Adding ASM flag ${asmflag}")
	get_property(_TEMP GLOBAL PROPERTY STAP_ASMFLAGS)
	list(APPEND _TEMP ${asmflag})
	set_property(GLOBAL PROPERTY STAP_ASMFLAGS ${_TEMP})
endmacro()

# Updates the global list of linker flags
macro(stap_build_configuration_append_linker_flag LINKER_FLAG)
	message(STATUS "Adding linker flag `${LINKER_FLAG}`")
	get_property(_TEMP GLOBAL PROPERTY STAP_LINKER_FLAGS)
	list(APPEND _TEMP ${LINKER_FLAG})
	set_property(GLOBAL PROPERTY STAP_LINKER_FLAGS ${_TEMP})
endmacro()

# Iterates over listed targets and sets compiler options for those
macro(stap_build_configuration_apply_flags_to_targets)
	get_property(_TEMP_STAP_TARGETS GLOBAL PROPERTY STAP_TARGETS)

	foreach(TARGET_NAME ${_TEMP_STAP_TARGETS})
		message(STATUS "Setting flags for target ${TARGET_NAME}...")
		get_property(_TEMP_CFLAGS GLOBAL PROPERTY STAP_CFLAGS)
		get_property(_TEMP_ASMFLAGS GLOBAL PROPERTY STAP_ASMFLAGS)
		get_property(_TEMP_LINKER_FLAGS GLOBAL PROPERTY STAP_LINKER_FLAGS)
		string(JOIN " " _TEMP_CFLAGS ${_TEMP_CFLAGS})
		string(JOIN " " _TEMP_ASMFLAGS ${_TEMP_ASMFLAGS})
		string(JOIN "," _TEMP_LINKER_FLAGS ${_TEMP_LINKER_FLAGS})
		message(STATUS "... C flags: ${_TEMP_CFLAGS}")
		message(STATUS "... ASM flags: ${_TEMP_ASMFLAGS}")
		message(STATUS "... Linker flags: ${_TEMP_LINKER_FLAGS}")
		target_compile_options(${TARGET_NAME} PRIVATE
			$<$<COMPILE_LANGUAGE:C>:SHELL:${_TEMP_CFLAGS}>
			$<$<COMPILE_LANGUAGE:ASM>:SHELL:${_TEMP_ASMFLAGS}>
		)
		set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)
		target_link_options(${TARGET_NAME} PRIVATE "SHELL:-Wl,${_TEMP_LINKER_FLAGS}")
	endforeach()
endmacro()

# Enqueues a target into the list of targets
macro(stap_build_configuration_apply_flags_to_target TARGET_NAME)
	get_property(_TEMP_STAP_TARGETS GLOBAL PROPERTY STAP_TARGETS)
	list(APPEND _TEMP_STAP_TARGETS ${TARGET_NAME})
	set_property(GLOBAL PROPERTY STAP_TARGETS ${_TEMP_STAP_TARGETS})
	message(STATUS "Added target ${TARGET_NAME}")
endmacro()
