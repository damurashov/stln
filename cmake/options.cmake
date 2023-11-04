
add_library(Options INTERFACE)

macro(bin_option option_name option_description option_default)
	option(${option_name} ${option_description} ${option_default})

	if(${option_name})
		target_compile_definitions(Options INTERFACE -D${option_name}=1)
	else()
		target_compile_definitions(Options INTERFACE -D${option_name}=0)
	endif()
endmacro()

bin_option(STAP_TARGET_STM32F412 ON)
