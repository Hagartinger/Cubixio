#pragma once

#include<mat4x4.hpp>

#include "Mesh.h"

class Object
{
public:
	Object();

	Mesh mesh_;
	glm::mat4 worldMatrix_;
};