#include "TexSheet.h"
#include <SOIL/SOIL.h>

glm::mat2x2 tex_sheet::getUV(unsigned int num)
{
    glm::uvec2 pos(num % size.x, num / size.x);
    glm::vec2 uvPosLU = _step * (glm::vec2)pos;
    glm::vec2 uvPosRD = uvPosLU + _step;

    return glm::mat2x2() = {uvPosLU.x, uvPosLU.y, uvPosRD.x, uvPosRD.y};
}

glm::umat2x2 tex_sheet::getUV(glm::uvec2 posInSheet)
{
    glm::vec2 uvPosLU = _step * (glm::vec2)posInSheet;
    glm::vec2 uvPosRD = uvPosLU + _step;

    return glm::mat2x2() = { uvPosLU.x, uvPosLU.y, uvPosRD.x, uvPosRD.y };
}

tex_sheet::tex_sheet(const char* pathToImage, glm::uvec2 size)
{
	int width, height;
	unsigned char* image = SOIL_load_image(pathToImage, &width, &height, 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
