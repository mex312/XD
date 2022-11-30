#include "GameObject.h"
#include "Core.h"

Transform& GameObject::getTransform()
{
	return _transform;
}

GameObject* GameObject::getParent()
{
	return _transform.parent->gameObject;
}

const std::set<GameObject*> GameObject::getChildren()
{
	std::set<GameObject*> out;
	for (auto child : _transform.children) {
		out.insert(child->gameObject);
	}
	return const_cast<std::set<GameObject*>&>(out);
}

GameObject::GameObject() : Object("New Object", Core::getNewId()), _transform(this), _components(0)
{}

GameObject::GameObject(std::string& name) : Object(name, Core::getNewId()), _transform(this), _components(0)
{
}

GameObject::GameObject(const char* name) : Object(name, Core::getNewId()), _transform(this), _components(0)
{
}

GameObject::~GameObject()
{
	/*for (auto component : components) {
		delete component;
	}*/
	_components.clear();
}
