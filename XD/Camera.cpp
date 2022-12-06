#include "Camera.h"
#include "GameObject.h"

glm::mat4 Camera::getViewMatrix()
{
	if (mode == PERSPECTIVE) {
		//return glm::perspectiveFov(fov, viewport.x, viewport.y, nearClip, farClip) * gameObject->transform.localMatrix;
		return glm::perspectiveFov(fov, viewport.x, viewport.y, nearClip, farClip) * glm::mat4_cast(gameObject->transform.rotation) * glm::translate(glm::mat4(1), -gameObject->transform.position);
	}
	else {
		return glm::mat4(1) * gameObject->transform.localMatrix;
	}
}

Camera::Camera(GameObject* gameObject, Camera_Modes mode) : Component("New Camera", gameObject), mode(mode)
{}

Camera::Camera(std::string name, GameObject * gameObject, Camera_Modes mode) : Component(name, gameObject), mode(mode)
{}

Camera::Camera(const char* name, GameObject * gameObject, Camera_Modes mode) : Component(name, gameObject), mode(mode)
{}
