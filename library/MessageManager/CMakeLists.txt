project(MessageManager)

add_subdirectory(include)
add_subdirectory(source)
	
add_library(${PROJECT_NAME} STATIC
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	)

target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_ROOT_DIR}/common)

set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT include/stdafx.h)
cotire(${PROJECT_NAME})