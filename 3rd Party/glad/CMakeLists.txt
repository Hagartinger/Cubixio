cmake_minimum_required( VERSION 3.2)

Project (Glad)

add_library( glad src/glad.c )

target_include_directories( glad PUBLIC "include/" )

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
	target_link_libraries( glad PRIVATE dl )
endif()
