#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <gtc/type_ptr.hpp>

#include <SDL_image.h>

Renderer::Renderer(SDL_Window* window)
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

	IMG_Init(IMG_INIT_JPG);
	//printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	IMG_Init(IMG_INIT_PNG);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	programID_ = glCreateProgram();

	unsigned int vertexShaderID, fragmentShaderID;
	{
		std::ifstream shaderSourceFile;
		shaderSourceFile.open("../resources/shaders/VertexShader.vert");
		if (!shaderSourceFile.is_open())
		{
			std::cout << "Error: Couldn't open vertexShader Source file.\n";
		}

		std::stringstream stream;
		stream << shaderSourceFile.rdbuf();

		std::string shaderSourceString = stream.str();
		const char* shaderSource = shaderSourceString.c_str();

		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &shaderSource, NULL);

		glCompileShader(vertexShaderID);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glAttachShader(programID_, vertexShaderID);
		
	}
	{
		std::ifstream shaderSourceFile;
		shaderSourceFile.open("../resources/shaders/FragmentShader.frag");
		if (!shaderSourceFile.is_open())
		{
			std::cout << "Error: Couldn't open FragmentShader Source file.\n";
		}

		std::stringstream stream;
		stream << shaderSourceFile.rdbuf();

		std::string shaderSourceString = stream.str();
		const char* shaderSource = shaderSourceString.c_str();

		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &shaderSource, NULL);

		glCompileShader(fragmentShaderID);

		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glAttachShader(programID_, fragmentShaderID);
	}

	glLinkProgram(programID_);

	int success;
	char infoLog[512];
	glGetProgramiv(programID_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID_);
}

void Renderer::draw()
{
	//clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setup camera matrix
	glm::mat4 viewMatrix = glm::lookAt(camera_.position_, camera_.position_ + camera_.eyeVector_, { 0.f, 1.f, 0.f });
	glm::mat4 projMatrix = glm::perspective(glm::radians(120.f), 4.f / 3.f, 0.001f, 100.f);

	unsigned int viewMatLocation = glGetUniformLocation(programID_, "uViewMatrix");
	unsigned int projMatLocation = glGetUniformLocation(programID_, "uProjectionMatrix");

	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));

	//here should be scene draw


	//and UI draw eventually

}

void Renderer::swapBuffers()
{
	SDL_GL_SwapWindow(window_);
}

void Renderer::moveCamera(float distance)
{
	camera_.position_.z += distance;
}

Camera::Camera()
{
	position_ = glm::vec3{ 0.f , 0.f, 3.f };
	eyeVector_ = glm::vec3{ 0.f, 0.f, -1.f };
}
