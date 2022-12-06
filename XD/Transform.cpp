#include "Transform.h"

glm::mat4 Transform::getLocalTransformMatrix()
{
	glm::mat4 out(1);
	out = glm::scale(out, scale);
	out *= glm::mat4_cast(rotation);
	out = glm::translate(out, position);
	return out;
}

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

Transform::Transform(GameObject* gameObject) : position(0), rotation(), scale(1), _parent(NULL), _children(), _gameObject(gameObject)
{}

Transform::Transform(GameObject* gameObject, Transform& parent) : position(0), rotation(), scale(0), _parent(&parent), _children(), _gameObject(gameObject)
{}

Transform::~Transform()
{
	for (auto child : _children) {
		child->_parent = NULL;
	}
	_children.clear();

	if (_parent != NULL) {
		auto thisIter = parent->_children.find(this);
		if (thisIter != parent->_children.end()) {
			parent->_children.erase(thisIter);
		}
	}
}
