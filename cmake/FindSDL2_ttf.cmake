SET(SDL2_ttf_PATH "" CACHE PATH "Path to SDL2")

SET(SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	${SDL2_ttf_PATH}
)

FIND_PATH(SDL2_ttf_INCLUDE_DIR SDL_ttf.h
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
	PATHS ${SEARCH_PATHS}
)

FIND_LIBRARY(SDL2_ttf
	NAMES SDL2_ttf
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x64 lib/x86
	PATHS ${SEARCH_PATHS}
)


SET(SDL2_ttf_DLL "" CACHE FILEPATH "Path to SDL2_ttf.dll")
INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_ttf SDL2_ttf_INCLUDE_DIR)

