#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>

#include "Renderer.h"

class Mesh
{
public:
	void draw()
	{
		glBindVertexArray(vertexArrayObject_);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, numberOfVerticies_);
	}

	static Mesh createTriangle()
	{
		Mesh result;
		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  1.f , 0.0f
		};

		result.numberOfVerticies_ = 3;

		glGenVertexArrays(1, &result.vertexArrayObject_);
		glBindVertexArray(result.vertexArrayObject_);

		unsigned int vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		return result;
	}
private:
	unsigned int vertexArrayObject_;
	unsigned int numberOfVerticies_;

	Mesh() = default;

	friend class MeshPrimitiveFactory;
};
class MeshPrimitiveFactory;
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

	auto triangle = Mesh::createTriangle();
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
		triangle.draw();
		renderer.swapBuffers();
	}


	SDL_Quit();
	return 0;
}
