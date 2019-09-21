cmake_minimum_required( VERSION 3.2)

project( Cubixio )

set( CMAKE_MODULE_PATH {$CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories( "${SDL2_INCLUDE_DIR}/../")

add_subdirectory( "3rd Party/glad")

add_executable( launcher src/main.cpp )

target_link_libraries( launcher PRIVATE glad  PUBLIC ${SDL2_LIBRARY} )

add_custom_command(TARGET launcher POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        ${SDL2_DLL}                                # <--this is in-file
        $<TARGET_FILE_DIR:launcher>)				   # <--this is out-file path
