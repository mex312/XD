#version 330 core

layout (location = 0) in vec3 raw_position;
layout (location = 1) in vec4 raw_color;
layout (location = 2) in vec2 raw_texCoord;

uniform mat4 transform;

out vec4 vertexColor;
out vec2 texCoord;

void main()
{
	//gl_Position = transform * vec4(raw_position, 1.0f);
	gl_Position = transform * vec4(raw_position, 1.0f);
	vertexColor = raw_color;
	texCoord = raw_texCoord;
}