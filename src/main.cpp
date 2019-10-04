#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"
#include "Mesh.h"

class Terrain;
class World;


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	//Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	

	auto window = SDL_CreateWindow("Cubixio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	
	Renderer renderer{ window };
	
	//World cubixland; // Initialisation of the 

	auto cube = MeshPrimitiveFactory::createCube();
	auto previousTimePoint = std::chrono::high_resolution_clock::now();
	
	while (true)
	{
		auto now = std::chrono::high_resolution_clock::now();
		double deltaTime = ( now - previousTimePoint ).count() / (double)std::nano::den;
		previousTimePoint = now;

		SDL_Event ev;
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
			break;

		if (ev.type == SDL_KEYDOWN)
		{
			switch (ev.key.keysym.sym)
			{
			case SDLK_w:
				renderer.moveCamera(deltaTime * 1.f);
				break;
			case SDLK_s:
				renderer.moveCamera(deltaTime * -1.f);
				break;
			default:
				break;
			}
		}
		
		renderer.draw();
		cube.draw();
		renderer.swapBuffers();
	}


	SDL_Quit();
	return 0;
}
