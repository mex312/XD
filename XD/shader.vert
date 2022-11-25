#version 330 core

layout (location = 0) in vec3 raw_position;
layout (location = 1) in vec2 raw_texCoord;
//layout (location = 2) in vec4 raw_color;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;



out vec4 vertexColor;
out vec2 texCoord;

void main()
{
	//gl_Position = transform * vec4(raw_position, 1.0f);
	gl_Position = u_projection * u_view * u_model * vec4(raw_position, 1.0f);
	//vertexColor = raw_color;
	vertexColor = vec4(1, 1, 1, 1);
	texCoord = raw_texCoord;
}