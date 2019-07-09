project(sfmllib)

set(SFML_DIR "lib/cmake/SFML/")
find_package(SFML 2.5 COMPONENTS audio window graphics system REQUIRED)

add_library(${PROJECT_NAME} STATIC dummy.cpp)
add_library(${PROJECT_NAME}_i INTERFACE)

target_include_directories(${PROJECT_NAME}_i INTERFACE include)
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		${PROJECT_NAME}_i
		sfml-audio
		sfml-graphics
		sfml-window
		sfml-system
	)
	
project_group(${PROJECT_NAME} external)