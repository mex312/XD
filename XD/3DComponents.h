#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>
#include <vector>

class GLShader;
class Camera;

struct vertex
{
public:
	glm::vec3 pos;
	glm::vec2 uv;
};


struct polygon
{
public:
	vertex vert1;
	vertex vert2;
	vertex vert3;
	bool enabled;
};

struct model
{
	std::list<polygon> polygons;

	std::list<polygon> getActivePolygons();

	void merge(const model& other);

	static model merge(const model& a, const model& b);

	model(std::list<polygon> polys) : polygons(polys) {}
	model(std::vector<polygon> polys);
	model() {}
};

struct Mesh
{
public:
	std::vector<float> vertexArray;
	GLuint VAO, VBO, texture, drawMode;

	void setTexture(GLuint texture);
	void setVertexArray(const std::list<polygon> & polys);
	void setVertexArray(const std::vector<polygon> & polys);
	void setVertexArray(const std::list<vertex> & vertices);
	void setVertexArray(const std::vector<vertex> & vertices);
	void setVertexArray(const std::vector<float> & vertexArray);

	void updateVAO();

	Mesh(const std::list<polygon>& polys, GLuint texture = 0, GLuint drawMode = GL_STATIC_DRAW);
	Mesh(const std::vector<polygon>& polys = std::vector<polygon>(), GLuint texture = 0, GLuint drawMode = GL_STATIC_DRAW);
};

namespace Core
{
	const unsigned int VERT_SIZE = 5;
	const unsigned int POLY_SIZE = VERT_SIZE * 3;

	void initVBO(GLuint VAO, GLuint VBO);

	void writeVertexToArray(float* arr, const vertex& vert);
	void writePolyonToArray(float* arr, const polygon& poly);

	void writePolygonsToVertexArray(const std::list<polygon> & polys, float * vertexArray);
	void writePolygonsToVertexArray(const std::vector<polygon> & polys, float * vertexArray);

	void writeVerticesToVertexArray(const std::list<vertex>& verts, float* vertexArray);
	void writeVerticesToVertexArray(const std::vector<vertex>& verts, float* vertexArray);
}