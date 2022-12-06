#pragma once
#include "Object.h"
#include "Transform.h"
class Component;

class GameObject : public Object
{
private:
	Transform _transform;
	std::set<Component*> _components;

public:
	bool isActive = true;

	Transform& getTransform();
	GameObject* getParent();
	const std::set<GameObject*> getChildren();
	const std::set<Component*> getComponents();

	__declspec (property(get = getTransform)) Transform& transform;
	__declspec (property(get = getParent)) GameObject* parent;
	__declspec (property(get = getChildren)) const std::set<GameObject*> children;
	__declspec (property(get = getComponents)) const std::set<Component*> components;

	void addComponent(Component* component);
	void removeComponent(Component* component);

	GameObject();
	GameObject(std::string& name);
	GameObject(const char* name);
	~GameObject();
};

