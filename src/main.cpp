#include <iostream>
#include <vector>
#include <chrono>

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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  1.f , 0.0f
	};


	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	std::vector<float> vecVert(std::begin(vertices), std::end(vertices));
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vecVert.size() * sizeof(float), vecVert.data(), GL_STATIC_DRAW);
	//position atribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


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
				render.moveCamera(deltaTime * 1.f);
				break;
			case SDLK_s:
				render.moveCamera(deltaTime * -1.f);
				break;
			default:
				break;
			}
		}
		render.draw();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		render.swapBuffers();
	}


	SDL_Quit();
	return 0;
}
