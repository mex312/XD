#include "3DComponents.h"
#include "Camera.h"
#include "GLShader.h"
#include "Core.h"

void Core::initVBO(GLuint VAO, GLuint VBO)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Core::writeVertexToArray(float * arr, const vertex& vert)
{
	*arr = vert.pos.x;
	arr++;
	*arr = vert.pos.y;
	arr++;
	*arr = vert.pos.z;
	arr++;
	*arr = vert.uv.x;
	arr++;
	*arr = vert.uv.y;
}

void Core::writePolyonToArray(float * arr, const polygon& poly)
{
	if (poly.enabled) {
		writeVertexToArray(arr, poly.vert1);
		arr += VERT_SIZE;
		writeVertexToArray(arr, poly.vert2);
		arr += VERT_SIZE;
		writeVertexToArray(arr, poly.vert3);
	}
}

void Core::writePolygonsToVertexArray(const std::list<polygon> & polys, float * vertexArray)
{
	for (auto & poly : polys) {
		writePolyonToArray(vertexArray, poly);
		vertexArray += POLY_SIZE;
	}
}
void Core::writePolygonsToVertexArray(const std::vector<polygon>& polys, float* vertexArray)
{
	for (auto& poly : polys) {
		writePolyonToArray(vertexArray, poly);
		vertexArray += POLY_SIZE;
	}
}

void Core::writeVerticesToVertexArray(const std::list<vertex>& verts, float* vertexArray)
{
	for (auto& vert : verts) {
		writeVertexToArray(vertexArray, vert);
		vertexArray += VERT_SIZE;
	}
}
void Core::writeVerticesToVertexArray(const std::vector<vertex>& verts, float* vertexArray)
{
	for (auto& vert : verts) {
		writeVertexToArray(vertexArray, vert);
		vertexArray += VERT_SIZE;
	}
}

void Mesh::setTexture(GLuint texture)
{
	this->texture = texture;
}

void Mesh::setVertexArray(const std::list<polygon> & polys)
{
	vertexArray.resize(polys.size() * Core::POLY_SIZE);
	Core::writePolygonsToVertexArray(polys, vertexArray.begin()._Ptr);
	updateVAO();
}

void Mesh::setVertexArray(const std::vector<polygon> & polys)
{
	vertexArray.resize(polys.size() * Core::POLY_SIZE);
	Core::writePolygonsToVertexArray(polys, vertexArray.begin()._Ptr);
	updateVAO();
}

void Mesh::updateVAO()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.begin()._Ptr, drawMode);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(const std::list<polygon> & polys, GLuint texture, GLuint drawMode) : vertexArray(vertexArray), texture(texture), drawMode(drawMode)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	Core::initVBO(VAO, VBO);

	vertexArray.resize(polys.size() * Core::POLY_SIZE);
	Core::writePolygonsToVertexArray(polys, vertexArray.begin()._Ptr);

	updateVAO();
}

Mesh::Mesh(const std::vector<polygon>& polys, GLuint texture, GLuint drawMod) : vertexArray(vertexArray), texture(texture), drawMode(drawMode)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	Core::initVBO(VAO, VBO);

	vertexArray.resize(polys.size() * Core::POLY_SIZE);
	Core::writePolygonsToVertexArray(polys, vertexArray.begin()._Ptr);

	updateVAO();
}

std::list<polygon> model::getActivePolygons()
{
	std::list<polygon> out;

	for (auto& n : polygons) {
		if (n.enabled) out.push_back(n);
	}

	return out;
}

void model::merge(const model& other)
{
	for (auto& n : other.polygons) {
		polygons.push_back(n);
	}
}

model model::merge(const model& a, const model& b)
{
	model out;

	out.polygons = a.polygons;
	for (auto& n : b.polygons) {
		out.polygons.push_back(n);
	}

	return out;
}

model::model(std::vector<polygon> polys)
{
	for (auto& n : polys) {
		polygons.push_back(n);
	}
}
