#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

struct tex_sheet
{
private:

	GLuint _texture;
	glm::uvec2 _size;
	unsigned int sampleNum;
	glm::vec2 _step;

public:

	GLuint getTexture() const { return _texture; }
	glm::uvec2 getSize() const { return _size; }

	glm::mat2x2 getUV(unsigned int num);
	glm::umat2x2 getUV(glm::uvec2 posInSheet);

	_declspec (property(get = getTexture)) GLuint texture;
	_declspec (property(get = getSize)) glm::uvec2 size;

	tex_sheet(GLuint texture, glm::uvec2 size) : _size(size), _texture(texture), sampleNum(size.x* size.y), _step(1.0f / (float)size.x, 1.0f / (float)size.y) {}
	tex_sheet(const char* pathToImage, glm::uvec2 size);
};

