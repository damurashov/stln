file(GLOB SOURCES "*.c")
add_library(stm32f4 ${SOURCES})
target_include_directories(stm32f4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_INCLUDE_DIRECTORIES})
target_link_libraries(stm32f4 PUBLIC stm32cubef4)
