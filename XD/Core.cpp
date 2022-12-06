#include "Core.h"
#include "Component.h"
#include "GameObject.h"
#include "Time.h"

long long nextId = 0;

std::set<GameObject*> _gameObjects;
std::set<Component*> _components;

void Core::updateAllActiveComponents()
{
    for (auto component : _components) {
        if (component->isActive && component->gameObject->isActive) {
            //printf("Updating %s\n", component->name.c_str());
            component->updateComponent();
        }
    }
}

long long Core::getNewId()
{
    nextId++;
    return nextId - 1;
}

void Core::addGameObject(GameObject* gameObject)
{
    _gameObjects.insert(gameObject);
}

void Core::addComponent(Component* component)
{
    _components.insert(component);
}

void Core::removeGameObject(GameObject* gameObject)
{
    auto iter = _gameObjects.find(gameObject);
    if (iter != _gameObjects.end()) {
        _gameObjects.erase(gameObject);
    }
}

void Core::removeComponent(Component* component)
{
    auto iter = _components.find(component);
    if (iter != _components.end()) {
        _components.erase(component);
    }
}

void Core::updateCore()
{
    Time::updateTime();
    Input::updateInput();
    updateAllActiveComponents();
}

void Core::initCore()
{
    Time::initTime();
    Input::initInput();
}
