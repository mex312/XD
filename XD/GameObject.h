#pragma once
#include <list>
#include "Object.h"
#include "Transform.h"
class Component;

class GameObject : public Object
{
private:
	Transform _transform;
	std::list<Component*> _components;

public:
	Transform& getTransform();
	GameObject* getParent();
	const std::set<GameObject*> getChildren();

	__declspec (property(get = getTransform)) Transform& transform;
	__declspec (property(get = getParent)) GameObject* parent;
	__declspec (property(get = getChildren)) const std::set<GameObject*> children;

	GameObject();
	GameObject(std::string& name);
	GameObject(const char* name);
	~GameObject();
};

