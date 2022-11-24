#ifndef GLSHADER_H
#define GLSHADER_H
#define GLEW_STATIC

#include <GL/glew.h>

class GLShader
{
public:
	GLuint program;

	GLShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
};

#endif