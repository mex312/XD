#include "3DComponents.h"

void writeVertexToArray(float* arr, const unsigned int& startPoint, const vertex& vert, const vec2& texPos)
{
	arr[startPoint + 0] = vert.pos.x;
	arr[startPoint + 1] = vert.pos.y;
	arr[startPoint + 2] = vert.pos.z;
	arr[startPoint + 3] = vert.uv.x;
	arr[startPoint + 4] = vert.uv.y;
	arr[startPoint + 5] = texPos.x;
	arr[startPoint + 6] = texPos.y;
}

//void CubeModel::writeToVertexArray(float* arr, unsigned int startPoint, vec3 modelPosition)
//{
//	Model::writeToVertexArray(arr, startPoint, modelPosition);
//}

unsigned int Model::getPolygonsNumber()
{
	return _polygonsNumber;
}

polygon* Model::getPolygons()
{
	return _polygons;
}

bool* Model::getActivePolygons()
{
	return _activePolygons;
}

vec2* Model::getTexturePositions()
{
	return _texturePositions;
}

void Model::setActivePolygon(unsigned int num, bool state)
{
	_activePolygons[num] = state;
}

void Model::setTexturePosition(unsigned int num, vec2 texPos)
{
	_texturePositions[num] = texPos;
}

void Model::writeToVertexArray(float* arr, unsigned int startPoint, vec3 modelPosition)
{
	unsigned int v = 0;
	vertex vertToDraw;
	for (int i = 0; i < _polygonsNumber; i++) {
		if (_activePolygons[i]) {
			unsigned int ptr = v * 21;
			vertToDraw = _polygons[i].vert1;
			vertToDraw.pos += modelPosition;
			writeVertexToArray(arr, startPoint + ptr, vertToDraw, _texturePositions[i]);
			ptr += 7;
			vertToDraw = _polygons[i].vert2;
			vertToDraw.pos += modelPosition;
			writeVertexToArray(arr, startPoint + ptr, vertToDraw, _texturePositions[i]);
			ptr += 7;
			vertToDraw = _polygons[i].vert3;
			vertToDraw.pos += modelPosition;
			writeVertexToArray(arr, startPoint + ptr, vertToDraw, _texturePositions[i]);
			v++;
		}
	}
}

Model::~Model()
{
	free(_polygons);
	free(_activePolygons);
	free(_texturePositions);
}

void CubeModel::setSideTexture(CubeSides side, vec2 texPos)
{
	setTexturePosition(side * 2, texPos);
	setTexturePosition(side * 2 + 1, texPos);
}

void CubeModel::setSideActive(CubeSides side, bool state)
{
	setActivePolygon(side * 2, state);
	setActivePolygon(side * 2 + 1, state);
}
