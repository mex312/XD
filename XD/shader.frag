#version 330 core

out vec4 color;

uniform sampler2D boxTexture;

in vec4 vertexColor;
in vec2 texCoord;

void main()
{
	//color = texture(boxTexture, texCoord);
	//color = vertexColor;
	color = texture(boxTexture, texCoord) * vertexColor;
}