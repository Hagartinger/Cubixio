#include "Mesh.h"

#include <glad/glad.h>
#include <vec3.hpp>

#include <memory>
#include <vector>

using Point = glm::vec3;

void Mesh::draw() const
{
	glBindVertexArray(vertexArrayObject_);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, numberOfVerticies_);
}

Mesh MeshPrimitiveFactory::createTriangle()
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
	return std::move(result);
}

Mesh MeshPrimitiveFactory::createCube()
{
	
	float vertices[] = {
	//position		      // texture coordinate
	-0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  //1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  //0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  //0.0f, 1.0f
	};


	Mesh result;

	result.numberOfVerticies_ = 6 * 6;

	glGenVertexArrays(1, &result.vertexArrayObject_);
	glBindVertexArray(result.vertexArrayObject_);

	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	return std::move(result);
	
	
	

	return Mesh();
}
