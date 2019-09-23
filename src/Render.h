#include <glad/glad.h>
#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera();
	~Camera() = default;
public:
	glm::vec3 position_;
	glm::vec3 eyeVector_;

};


class Render
{
public:
	Render(SDL_Window* window);
	~Render() = default;

	void draw();

	void swapBuffers();

	void moveCamera(float distance);
private:
	SDL_Window* window_;
	unsigned int programID_;
	Camera camera_;
};

