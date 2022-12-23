#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <set>

class GameObject;

class Transform
{
private:
	GameObject* _gameObject;
	std::set<Transform*> _children;
	Transform* _parent;

	glm::vec3 lastPos;
	glm::vec3 lastScl;
	glm::quat lastRot;

	glm::mat4 localMat = glm::mat4(1);
	glm::mat4 globalMat = glm::mat4(1);

	void recalcMartix();

	bool isMoved();

public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;

	//glm::vec3 getPostionAsGlobal();
	//glm::vec3 getScaleAsGlobal();
	//glm::quat getRotationAsGlobal();

	glm::mat4 getLocalTransformMatrix();
	glm::mat4 getGlobalTransformMatrix();

	Transform* getParent();
	GameObject* getGameObject();
	const std::set<Transform*> getChildren();

	//__declspec (property(get = getPostionAsGlobal)) glm::vec3 globalPosition;
	//__declspec (property(get = getScaleAsGlobal)) glm::vec3 globalScale;
	//__declspec (property(get = getRotationAsGlobal)) glm::quat globalRotation;

	__declspec (property(get = getLocalTransformMatrix)) glm::mat4 localMatrix;
	__declspec (property(get = getGlobalTransformMatrix)) glm::mat4 globalMatrix;

	__declspec (property(get = getParent)) Transform* parent;
	__declspec (property(get = getGameObject)) GameObject* gameObject;
	__declspec (property(get = getChildren)) const std::set<Transform*> children;

	void setParent(Transform* newParent);


	Transform(GameObject* gameObject);
	Transform(GameObject* gameObject, Transform& parent);
	~Transform();
};

