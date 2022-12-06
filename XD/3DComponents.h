#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

struct vertex
{
public:
	vec3 pos;
	vec2 uv;
};


struct polygon
{
public:
	vertex vert1;
	vertex vert2;
	vertex vert3;
};



class Model
{
protected:
	polygon* _polygons;
	bool* _activePolygons;
	vec2* _texturePositions;
	unsigned int _polygonsNumber;

public:

	unsigned int getPolygonsNumber();
	polygon* getPolygons();
	bool* getActivePolygons();
	vec2* getTexturePositions();

	void setActivePolygon(unsigned int num, bool state);
	void setTexturePosition(unsigned int num, vec2 texPos);

	void writeToVertexArray(float* arr, unsigned int startPoint, vec3 modelPosition);

	~Model();
};


class CubeModel : public Model
{
public:
	enum CubeSides {
		UP,
		DOWN,
		FRONT,
		BACK,
		RIGHT,
		LEFT
	};

	void setSideTexture(CubeSides side, vec2 texPos);
	void setSideActive(CubeSides side, bool state);

	CubeModel() {

		_polygons = new polygon[12]{
			//up
			{
				{vec3(1, 1, 0), vec2(1, 0)},
				{vec3(0, 1, 0), vec2(0, 0)},
				{vec3(0, 1, 1), vec2(0, 1)},
			},{
				{vec3(1, 1, 1), vec2(1, 1)},
				{vec3(1, 1, 0), vec2(1, 0)},
				{vec3(0, 1, 1), vec2(0, 1)},
			},
			//down
			{
				{vec3(0, 0, 0), vec2(0, 1)},
				{vec3(1, 0, 0), vec2(1, 1)},
				{vec3(1, 0, 1), vec2(1, 0)},
			},{
				{vec3(0, 0, 1), vec2(0, 0)},
				{vec3(0, 0, 0), vec2(0, 1)},
				{vec3(1, 0, 1), vec2(1, 0)},
			},
			//front
			{
				{vec3(0, 0, 1), vec2(0, 1)},
				{vec3(1, 1, 1), vec2(1, 0)},
				{vec3(0, 1, 1), vec2(0, 0)},
			},{
				{vec3(1, 0, 1), vec2(1, 1)},
				{vec3(1, 1, 1), vec2(1, 0)},
				{vec3(0, 0, 1), vec2(0, 1)},
			},
			//back
			{
				{vec3(0, 1, 0), vec2(1, 0)},
				{vec3(1, 1, 0), vec2(0, 0)},
				{vec3(0, 0, 0), vec2(1, 1)},
			},{
				{vec3(1, 1, 0), vec2(0, 0)},
				{vec3(1, 0, 0), vec2(0, 1)},
				{vec3(0, 0, 0), vec2(1, 1)},
			},
			//right
			{
				{vec3(1, 1, 0), vec2(1, 0)},
				{vec3(1, 1, 1), vec2(0, 0)},
				{vec3(1, 0, 1), vec2(0, 1)},
			},{
				{vec3(1, 0, 0), vec2(1, 1)},
				{vec3(1, 1, 0), vec2(1, 0)},
				{vec3(1, 0, 1), vec2(0, 1)},
			},
			//left
			{
				{vec3(0, 1, 1), vec2(1, 0)},
				{vec3(0, 1, 0), vec2(0, 0)},
				{vec3(0, 0, 1), vec2(1, 1)},
			},{
				{vec3(0, 1, 0), vec2(0, 0)},
				{vec3(0, 0, 0), vec2(0, 1)},
				{vec3(0, 0, 1), vec2(1, 1)},
			}
		};

		_activePolygons = new bool[12]{
			true, true,
			true, true,
			true, true,
			true, true,
			true, true,
			true, true,
		};

		_texturePositions = new vec2[12]();

		_polygonsNumber = 12;

	}

	//void writeToVertexArray(float* arr, unsigned int startPoint, vec3 modelPosition);
};