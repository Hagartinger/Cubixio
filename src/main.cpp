#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <mat4x4.hpp>

#include "Renderer.h"
#include "Mesh.h"
#include "Object.h"


class World;

const int cScreenWidth = 800;
const int cScreenHeight = 600;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	//Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	auto window = SDL_CreateWindow("Cubixio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cScreenWidth, cScreenHeight, SDL_WINDOW_OPENGL);
	
	Renderer renderer{ window };
	
	std::vector<Object> cubes;
	for (int i = 0; i < 4; i++)
	{
		Object cube;
		cube.worldMatrix_ = glm::translate(cube.worldMatrix_, { i * 1.2, 0,0 });
		cubes.push_back(std::move(cube));
	}
	
	auto previousTimePoint = std::chrono::high_resolution_clock::now();
	
	while (true)
	{
		auto now = std::chrono::high_resolution_clock::now();
		double deltaTime = ( now - previousTimePoint ).count() / (double)std::nano::den;
		previousTimePoint = now;

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				SDL_Quit();
				return 0;
			}

			if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_w:
					renderer.moveCamera(deltaTime * 5.f);
					break;
				case SDLK_s:
					renderer.moveCamera(deltaTime * -5.f);
					break;
				default:
					break;
				}
			}
		}
		renderer.prepareScene();

		for ( auto& cube : cubes )
		{
			renderer.draw(cube);
		}

		renderer.swapBuffers();
	}


	SDL_Quit();
	return 0;
}
