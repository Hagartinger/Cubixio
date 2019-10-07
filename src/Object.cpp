#include "Object.h"

Object::Object()
	: mesh_{MeshPrimitiveFactory::createCube()}
	, worldMatrix_{ glm::mat4(1.)}
{
}
