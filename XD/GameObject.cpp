#include "GameObject.h"
#include "Core.h"
#include "Component.h"

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

const std::set<Component*> GameObject::getComponents()
{
	return const_cast<std::set<Component*>&>(_components);
}

void GameObject::addComponent(Component* component)
{
	_components.insert(component);
}

void GameObject::removeComponent(Component* component)
{
	auto iter = _components.find(component);
	if (iter != _components.end()) {
		_components.erase(iter);
	}
}

GameObject::GameObject() : Object("New Object", Core::getNewId()), _transform(this), _components()
{}

GameObject::GameObject(std::string& name) : Object(name, Core::getNewId()), _transform(this), _components()
{
}

GameObject::GameObject(const char* name) : Object(name, Core::getNewId()), _transform(this), _components()
{
}

GameObject::~GameObject()
{
	printf("Deleting %s with id %lld\n", name.c_str(), id);

	auto componentsToDelete = components;
	_components.clear();
	for (auto component : componentsToDelete) {
		printf("%s\n", component->name.c_str());
		delete component;
	}

	for (auto child : children) {
		delete child;
	}

	Core::removeGameObject(this);
}
