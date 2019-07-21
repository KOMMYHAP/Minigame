project(Snowflake)

find_package(boost 1.7 COMPONENTS format REQUIRED)

add_subdirectory(include)
add_subdirectory(source)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})
	
target_include_directories(${PROJECT_NAME} PUBLIC 
	include
	${Boost_INCLUDE_DIRS})
	
target_link_libraries(${PROJECT_NAME} 
	baselib
	sfmllib
	opencvlib
	${Boost_format_LIBRARY})

set_precompiled_header(${PROJECT_NAME} "include/stdafx_game.h")


project_group(${PROJECT_NAME} game)