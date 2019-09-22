#include "Render.h"

#include <iostream>

Render::Render(SDL_Window* window)
	: window_{ window }
{
	auto context = SDL_GL_CreateContext(window);

	if (context == NULL)
	{
		std::cout << "Error: Couldn't initialise OpenGL context\n";
		std::terminate();
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::terminate();
	}

	glClearColor(0, 0, 0, 0);
}

void Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::swapBuffers()
{
	SDL_GL_SwapWindow(window_);
}
