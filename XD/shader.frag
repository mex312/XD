#version 330 core

out vec4 color;

uniform sampler2D u_texSheet;

in vec4 testColor;

in vec2 texCoord;

void main()
{
	//color = texture(u_texSheet, vec2(0.9, 0.1));
	color = texture(u_texSheet, texCoord);
	//color = testColor;
	if(color.a <= 0.0f) {
		discard;
	}
}