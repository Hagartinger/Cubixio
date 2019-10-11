# Cubixio
## How to Build
**Requirements:**
- cmake 3.2 or higer https://cmake.org/ 
- SDL2 Development library ( https://www.libsdl.org/download-2.0.php ) 
- SDL2-image Development library ( https://www.libsdl.org/projects/SDL_image/ )
- SDL2-ttf Development library ( https://www.libsdl.org/projects/SDL_ttf/ )
- If you are Linux user - make sure you have at least gcc 9.0 or higher

1. Create a directory called "build". 
2. Open cmake-gui and set root directory of a project as a source directory, and "build" directory as, you've guessed it, build directory. 
3. Open cmake-gui and specify SDL2_PATH (it's a hint for Cmake where it should search for SDL2). 
3.1 Repeat step 3 for SDL2_image and SDL2_ttf library if needed.
4. run Cmake. 

If everything went well you should have a project for IDE of your choice
