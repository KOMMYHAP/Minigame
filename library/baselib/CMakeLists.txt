project(baselib)

find_package(boost 1.70 REQUIRED COMPONENTS format)

add_subdirectory(include)
add_subdirectory(source)

add_library(${PROJECT_NAME}_i INTERFACE)
add_library(${PROJECT_NAME} STATIC ${SRCS})
project_group(${PROJECT_NAME} library)

target_link_libraries(${PROJECT_NAME} PUBLIC
	${PROJECT_NAME}_i
	${Boost_FORMAT_LIBRARY})

target_include_directories(${PROJECT_NAME}_i INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

set_precompiled_header(${PROJECT_NAME} "include/basic_defs.h")
