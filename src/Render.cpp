#include "Render.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

void Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::swapBuffers()
{
	SDL_GL_SwapWindow(window_);
}
