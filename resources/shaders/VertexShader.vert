#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexturePos;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec2 TexturePos;

void main()
{
	gl_Position = uProjectionMatrix * uViewMatrix * vec4(inPos, 1.0);

	TexturePos = inTexturePos;
}
