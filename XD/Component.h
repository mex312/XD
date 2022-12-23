#pragma once
#include "Object.h"
class GameObject;

class Component : public Object
{
private:
	GameObject* _gameObject;

protected:
	Component(GameObject* gameObject);
	Component(std::string& name, GameObject* gameObject);
	Component(const char* name, GameObject* gameObject);

public:
	bool isActive = true;

	GameObject* getGameObject();

	__declspec (property(get = getGameObject)) GameObject* gameObject;

	virtual void updateComponent() = 0;

	virtual ~Component();
};

