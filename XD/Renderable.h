#pragma once
#include "Component.h"
#include "3DComponents.h"
#include "GLShader.h"

namespace Core
{
	static GLShader* defaultShader;
}

class Renderable : public Component
{
public:
	GLShader * shader;

	void updateComponent();

	virtual void draw(Camera* camera) = 0;

	Renderable(GameObject* gameObject, GLShader * shader = (GLShader*)Core::defaultShader);
	Renderable(std::string& name, GameObject* gameObject, GLShader * shader = (GLShader*)Core::defaultShader);
	Renderable(const char* name, GameObject* gameObject, GLShader * shader = (GLShader*)Core::defaultShader);

	virtual ~Renderable() {}
};

class MeshRenderable : public Renderable
{
public:
	Mesh mesh;

	void draw(Camera* camera);

	MeshRenderable(GameObject* gameObject, const Mesh& mesh, GLShader* shader = (GLShader*)Core::defaultShader);
	MeshRenderable(std::string& name, GameObject* gameObject, const Mesh& mesh, GLShader* shader = (GLShader*)Core::defaultShader);
	MeshRenderable(const char* name, GameObject* gameObject, const Mesh& mesh, GLShader* shader = (GLShader*)Core::defaultShader);
};