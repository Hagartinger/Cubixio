#include <glad/glad.h>
#include <SDL.h>
#include <glm.hpp>

class Render
{
public:
	Render(SDL_Window* window);
	~Render() = default;

	void draw();

	void swapBuffers();
private:
	SDL_Window* window_;
};
