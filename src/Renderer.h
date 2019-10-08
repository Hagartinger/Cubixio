#pragma once

#include <glad/glad.h>
#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <filesystem>


class Object;

class Camera
{
public:
	Camera();
	~Camera() = default;
public:
	glm::vec3 position_;
	glm::vec3 eyeVector_;

};

class Shader
{
public:
	Shader(std::filesystem::path vertexShader, std::filesystem::path fragmentShader);
	Shader() {};
	unsigned int programID_;
};



class Renderer
{
public:
	Renderer(SDL_Window* window);
	~Renderer() = default;

	void prepareScene();

	void draw(Object& object);

	void swapBuffers();

	void moveCamera(float distance);
private:
	SDL_Window* window_;
	Camera camera_;
	Shader sceneShader_;
	Shader uiShader_;
};

