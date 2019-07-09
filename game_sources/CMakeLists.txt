project(Game)

find_package(boost 1.7 COMPONENTS format REQUIRED)

add_subdirectory(include)
add_subdirectory(source)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})
	
target_include_directories(${PROJECT_NAME} PRIVATE 
	include
	${PROJECT_ROOT_DIR}/external/SFML/include
	${Boost_INCLUDE_DIRS})
	
target_link_libraries(${PROJECT_NAME} 
	baselib
	gamelib
	mathlib
	sfmllib
	${Boost_format_LIBRARY}
	)

set_precompiled_header(${PROJECT_NAME} "include/stdafx_${PROJECT_NAME}.h")