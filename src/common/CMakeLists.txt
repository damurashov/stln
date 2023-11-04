# Specify source files
file(GLOB SOURCES "./*.c" "./*.s")

# Build the library
add_executable(application ${SOURCES})
message(STATUS "Linking libraries: ${APPLICATION_TARGET_LIBRARIES}")
target_link_libraries(application PRIVATE ${APPLICATION_TARGET_LIBRARIES})
stap_build_configuration_apply_flags_to_target(application)
