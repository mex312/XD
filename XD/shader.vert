#version 330 core

layout (location = 0) in vec3 raw_position;
layout (location = 1) in vec2 raw_uv;
layout (location = 2) in vec2 raw_texPos;

uniform mat4 u_view;
uniform mat4 u_model;
uniform vec2 u_texNumInv;

out vec4 testColor;

out vec2 texCoord;

void main()
{

	gl_Position = u_view * u_model * vec4(raw_position, 1.0f);
	//testColor = gl_Position;
	//testColor = vec4(1, 1, 1, 1);
	testColor = vec4(u_texNumInv, 0, 1);

	//float x = u_texNumInv.x * raw_uv.x + u_texNumInv.x * raw_texPos.x;
	//float y = u_texNumInv.y * raw_uv.y + u_texNumInv.y * raw_texPos.y;
	//texCoord = vec2(x, y);

	texCoord = u_texNumInv * raw_uv + u_texNumInv * raw_texPos;
	
	//texCoord = raw_texPos;
}