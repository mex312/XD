#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <set>

class GameObject;

class Transform
{
private:
	GameObject* _gameObject;
	std::set<Transform*> _children;
	Transform* _parent;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3& getPostionAsGlobal();
	glm::vec3& getRotationAsGlobal();
	glm::vec3& getScaleAsGlobal();

	Transform* getParent();
	GameObject* getGameObject();
	const std::set<Transform*> getChildren();

	__declspec (property(get = getPostionAsGlobal)) glm::vec3& globalPosition;
	__declspec (property(get = getPostionAsGlobal)) glm::vec3& globalRotation;
	__declspec (property(get = getPostionAsGlobal)) glm::vec3& globalScale;

	__declspec (property(get = getParent)) Transform* parent;
	__declspec (property(get = getGameObject)) GameObject* gameObject;
	__declspec (property(get = getChildren)) const std::set<Transform*> children;

	void setParent(Transform* newParent);


	Transform(GameObject* gameObject);
	Transform(GameObject* gameObject, Transform& parent);
	~Transform();
};

