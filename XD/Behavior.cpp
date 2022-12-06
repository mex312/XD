#include "Behavior.h"

void Behavior::updateComponent()
{
	Update();
}

Behavior::Behavior(GameObject* gameObject) : Component("New Behavior", gameObject)
{}

Behavior::Behavior(std::string& name, GameObject* gameObject) : Component(name, gameObject)
{}

Behavior::Behavior(const char* name, GameObject* gameObject) : Component(name, gameObject)
{}
