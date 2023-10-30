
foreach(TARGET ${APPLICATION_TARGET_LIBRARIES})
	add_subdirectory(target/${TARGET})
endforeach()

add_subdirectory(common)
