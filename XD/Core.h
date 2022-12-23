#pragma once
#include <set>
#include <list>
#include <vector>
#include "Time.h"
#include "Input.h"
#include "3DComponents.h"

class GameObject;
class Component;
class Renderable;

namespace Core
{
	void setActiveShader(GLShader * shader);
	void setActiveCamera(Camera * camera);

	void updateAllActiveComponents();

	long long getNewId();
	void addGameObject(GameObject* gameObject);
	void addComponent(Component* component);
	void addRenderableToRender(Renderable* model);
	void removeGameObject(GameObject* gameObject);
	void removeComponent(Component* component);
	float const* getVertexArray();
	unsigned int getVertexArraySize();

	void updateCore();
	void initCore();	
};