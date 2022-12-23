#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

class GLShader
{
public:
	GLuint program;

	GLShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	~GLShader() { glDeleteProgram(program); }
};