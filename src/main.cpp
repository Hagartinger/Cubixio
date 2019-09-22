#include <iostream>

#include <SDL.h>

#include "Render.h"
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	//Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	auto window = SDL_CreateWindow("Cubixio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	
	Render render{ window };
	
	while (true)
	{
		SDL_Event ev;
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
			break;

		render.draw();

		render.swapBuffers();
	}


	SDL_Quit();
	return 0;
}
