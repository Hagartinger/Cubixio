#pragma once 

class Mesh
{
public:
	void draw() const;

private:
	unsigned int vertexArrayObject_;
	unsigned int numberOfVerticies_;

	Mesh() = default;

	friend class MeshPrimitiveFactory;
};


class MeshPrimitiveFactory
{
public:
	static Mesh createTriangle();
	static Mesh createCube();
private:
	MeshPrimitiveFactory() = delete;
};