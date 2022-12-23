#include "Core.h"
#include "Component.h"
#include "GameObject.h"
#include "Time.h"
#include "Renderable.h"

long long nextId = 0;

std::set<GameObject*> _gameObjects;
std::set<Component*> _components;
std::set<Renderable*> _renderables;

unsigned int _vertexArraySize;
float* _vertexArray;

GLShader* activeShader;
Camera* activeCamera;

void Core::setActiveShader(GLShader * shader)
{
    activeShader = shader;
}

void Core::setActiveCamera(Camera * camera)
{
    activeCamera = camera;
}

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

void Core::addRenderableToRender(Renderable* model)
{
    _renderables.insert(model);
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

float const* Core::getVertexArray()
{
    return _vertexArray;
}

unsigned int Core::getVertexArraySize()
{
    return _vertexArraySize;
}

void Core::updateCore()
{
    _renderables.clear();
    Time::updateTime();
    Input::updateInput();
    updateAllActiveComponents();
    for (auto renderable : _renderables) {
        renderable->draw(activeCamera);
    }
}

void Core::initCore()
{
    Time::initTime();
    Input::initInput();
}
