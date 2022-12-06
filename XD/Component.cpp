#include "Component.h"
#include "GameObject.h"
#include "Core.h"

GameObject* Component::getGameObject()
{
    return _gameObject;
}

Component::Component(GameObject* gameObject) : Object("New Component", Core::getNewId()), _gameObject(gameObject)
{
    gameObject->addComponent(this);
    Core::addComponent(this);
}

Component::Component(std::string& name, GameObject* gameObject) : Object(name, Core::getNewId()), _gameObject(gameObject)
{
    gameObject->addComponent(this);
    Core::addComponent(this);
}

Component::Component(const char* name, GameObject* gameObject) : Object(name, Core::getNewId()), _gameObject(gameObject)
{
    gameObject->addComponent(this);
    Core::addComponent(this);
}

Component::~Component()
{
    printf("Deleting %s\n", name.c_str());

    if (_gameObject != NULL) {
        _gameObject->removeComponent(this);
        _gameObject = NULL;
    }

    Core::removeComponent(this);
}

