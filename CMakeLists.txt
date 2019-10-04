cmake_minimum_required( VERSION 3.14)

project( Cubixio )

set( CMAKE_MODULE_PATH {$CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

add_subdirectory( "3rd Party/glad")

file(GLOB SRC_FILES src/*.cpp src/*.h)

add_executable( launcher ${SRC_FILES} )

target_compile_features(launcher PUBLIC cxx_std_17)

target_include_directories( launcher 
	PUBLIC 
		"${SDL2_INCLUDE_DIR}" 
		"${SDL2_image_INCLUDE_DIR}"
		#"${SDL2_ttf_INCLUDE_DIR}"
		"${CMAKE_SOURCE_DIR}/3rd Party/glm-0.9.9.6/glm"
)

target_link_libraries( launcher 
	PRIVATE 
		glad  
	PUBLIC 
		${SDL2_LIBRARY} 
		${SDL2_image}
)

add_custom_command(TARGET launcher 
	POST_BUILD										   # Adds a post-build event to launcher
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
			${SDL2_DLL}                                # <--this is in-file
			$<TARGET_FILE_DIR:launcher>				   # <--this is out-file path
)
