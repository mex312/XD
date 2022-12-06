#pragma once
#include "Component.h"
#include <string>
class GameObject;

class Behavior : public Component
{
protected:
	void updateComponent();

public:
	virtual void Update() = 0;

	Behavior(GameObject* gameObject);
	Behavior(std::string& name, GameObject* gameObject);
	Behavior(const char* name, GameObject* gameObject);
};

