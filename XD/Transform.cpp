#include "Transform.h"

Transform* Transform::getParent()
{
	return _parent;
}

GameObject* Transform::getGameObject()
{
	return _gameObject;
}

const std::set<Transform*> Transform::getChildren()
{
	return const_cast<std::set<Transform*>&>(_children);
}

void Transform::setParent(Transform* newParent)
{
	if (_parent != NULL) {
		_parent->_children.erase(_parent->_children.find(this));
	}
	_parent = newParent;
	_parent->_children.insert(this);
}

Transform::Transform(GameObject* gameObject) : position(0), rotation(0), scale(1), _parent(NULL), _children(), _gameObject(gameObject)
{}

Transform::Transform(GameObject* gameObject, Transform& parent) : position(0), rotation(0), scale(0), _parent(&parent), _children(), _gameObject(gameObject)
{}

Transform::~Transform()
{
	/*for (auto child : children) {
		delete child;
	}*/
	_children.clear();

	if (_parent != NULL) {
		parent->_children.erase(parent->_children.find(this));
	}
}
