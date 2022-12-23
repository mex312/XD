#include "Renderable.h"
#include "Core.h"
#include "GameObject.h"
#include "GLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

void Renderable::updateComponent()
{
	Core::addRenderableToRender(this);
}

Renderable::Renderable(GameObject* gameObject, GLShader* shader) : Component("New Renderable", gameObject), shader(shader)
{
}

Renderable::Renderable(std::string& name, GameObject* gameObject, GLShader* shader) : Component(name, gameObject), shader(shader)
{
}

Renderable::Renderable(const char* name, GameObject* gameObject, GLShader* shader) : Component(name, gameObject), shader(shader)
{
}


void MeshRenderable::draw(Camera* camera)
{
	GLuint u_view = glGetUniformLocation(shader->program, "u_view");
	GLuint u_model = glGetUniformLocation(shader->program, "u_model");
	GLuint u_texNumInv = glGetUniformLocation(shader->program, "u_texNumInv");

	shader->use();

	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(camera->view));
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(gameObject->transform.globalMatrix));
	glUniform2f(u_texNumInv, 1.0f / 1.0f, 1.0f / 3.0f);

	glBindVertexArray(mesh.VAO);
	glBindTexture(GL_TEXTURE_2D, mesh.texture);

	glDrawArrays(GL_TRIANGLES, 0, mesh.vertexArray.size() / Core::VERT_SIZE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

MeshRenderable::MeshRenderable(GameObject* gameObject, const Mesh & mesh, GLShader* shader) : Renderable(gameObject, shader), mesh(mesh)
{
}

MeshRenderable::MeshRenderable(std::string& name, GameObject* gameObject, const Mesh& mesh, GLShader* shader) : Renderable(name, gameObject, shader), mesh(mesh)
{
}

MeshRenderable::MeshRenderable(const char* name, GameObject* gameObject, const Mesh& mesh, GLShader* shader) : Renderable(name, gameObject, shader), mesh(mesh)
{
}