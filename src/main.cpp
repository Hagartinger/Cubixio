#include <iostream>

#include <glad/glad.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	//Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	auto window = SDL_CreateWindow("Cubixio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	
	auto context = SDL_GL_CreateContext(window);

	if (context == NULL)
	{
		std::cout << "Error: Couldn't initialise OpenGL context\n";
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	float red = 0;
	
	while (true)
	{
		SDL_Event ev;
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
			break;

		red += 0.01;
		glClearColor(std::sin(red), std::sin(red * 3), std::sin(red * red), 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
		
	}


	SDL_Quit();
	return 0;
}
