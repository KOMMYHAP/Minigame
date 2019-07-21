project(opencvlib)

find_package(OpenCV 4 REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} INTERFACE ${OpenCV_INCLUDE_DIRS})