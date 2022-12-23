#include "Transform.h"

void Transform::recalcMartix()
{
	if (parent != nullptr) {
		parent->recalcMartix();
	}

	if (isMoved()) {
		localMat = glm::mat4(1);
		localMat = glm::translate(glm::scale(localMat, scale) * glm::mat4_cast(rotation), position);
		if (parent == nullptr) globalMat = localMat;
		else globalMat = localMat * parent->globalMat;
	}
}

bool Transform::isMoved()
{
	return rotation != lastRot || position != lastPos || scale != lastScl;
}

glm::mat4 Transform::getLocalTransformMatrix()
{
	recalcMartix();
	return localMat;
}

glm::mat4 Transform::getGlobalTransformMatrix()
{
	recalcMartix();
	return globalMat;
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
