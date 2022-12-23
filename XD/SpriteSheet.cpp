#include "SpriteSheet.h"
#include <SOIL/SOIL.h>

void TexMap::generateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, texMap);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TexMap::TexMap(const char* texMapPath, const glm::uvec2 & texMapSize) : texMapSize(texMapSize)
{
	int width, height;
	unsigned char* image = SOIL_load_image(texMapPath, &width, &height, 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &texMap);
	glBindTexture(GL_TEXTURE_2D, texMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TexMap::TexMap(unsigned char* texMapImage, const glm::uvec2& texMapSize)
{
	int width, height;

	glGenTextures(1, &texMap);
	glBindTexture(GL_TEXTURE_2D, texMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texMapImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}
