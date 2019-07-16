project(sfmllib)

add_library(${PROJECT_NAME} INTERFACE IMPORTED GLOBAL)

set(PATH_PREFIX "${CMAKE_CURRENT_LIST_DIR}/lib")

set(COMMON_CONFIG_LIB 
	"${PATH_PREFIX}/flac.lib;\
${PATH_PREFIX}/freetype.lib;\
${PATH_PREFIX}/ogg.lib;\
${PATH_PREFIX}/openal32.lib;\
${PATH_PREFIX}/vorbis.lib;\
${PATH_PREFIX}/vorbisenc.lib;\
${PATH_PREFIX}/vorbisfile.lib;\
opengl32.lib;winmm.lib;gdi32.lib")

target_link_directories(${PROJECT_NAME} INTERFACE ${PATH_PREFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES 
	INTERFACE_LINK_LIBRARIES
		"${COMMON_CONFIG_LIB};\
$<$<CONFIG:RelWithDebInfo>:\
${PATH_PREFIX}/sfml-graphics-s.lib;\
${PATH_PREFIX}/sfml-audio-s.lib;\
${PATH_PREFIX}/sfml-main.lib;\
${PATH_PREFIX}/sfml-system-s.lib;\
${PATH_PREFIX}/sfml-window-s.lib;\
${PATH_PREFIX}/sfml-system-s.lib;>\
$<$<CONFIG:Debug>:\
${PATH_PREFIX}/sfml-graphics-s-d.lib;\
${PATH_PREFIX}/sfml-audio-s-d.lib;\
${PATH_PREFIX}/sfml-main-d.lib;\
${PATH_PREFIX}/sfml-system-s-d.lib;\
${PATH_PREFIX}/sfml-window-s-d.lib;\
${PATH_PREFIX}/sfml-system-s-d.lib;>")
	
set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include")
target_compile_definitions(${PROJECT_NAME} INTERFACE SFML_STATIC)