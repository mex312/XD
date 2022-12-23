#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class TexMap
{
public:
	GLuint texMap;

	glm::uvec2 texMapSize;

	void generateMipmap();

	TexMap(const char * texMapPath, const glm::uvec2& texMapSize);
	TexMap(unsigned char * texMapImage, const glm::uvec2& texMapSize);

	~TexMap() { glDeleteTextures(1, &texMap); }
};

