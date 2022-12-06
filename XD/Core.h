#pragma once
#include <set>
#include "Time.h"
#include "Input.h"
class GameObject;
class Component;

class Core
{
private:

	static void updateAllActiveComponents();

public:
	static long long getNewId();
	static void addGameObject(GameObject* gameObject);
	static void addComponent(Component* component);
	static void removeGameObject(GameObject* gameObject);
	static void removeComponent(Component* component);

	static void updateCore();
	static void initCore();
};

