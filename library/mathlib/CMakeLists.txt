project(mathlib)

add_subdirectory(include)
add_subdirectory(source)

add_library(${PROJECT_NAME}_i INTERFACE)
add_library(${PROJECT_NAME} STATIC ${SRCS})
project_group(${PROJECT_NAME} library)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_i)
target_link_libraries(${PROJECT_NAME}_i INTERFACE baselib_i)

target_include_directories(${PROJECT_NAME}_i INTERFACE include)
