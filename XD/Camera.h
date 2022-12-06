#pragma once
#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Modes {
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera : public Component
{
protected:
	void updateComponent() {};

public:
	Camera_Modes mode;
	float fov = 1.5f;
	glm::vec2 viewport = glm::vec2(800, 600);
	float nearClip = 0.1f;
	float farClip = 100;

	glm::mat4 getViewMatrix();

	_declspec (property(get = getViewMatrix)) glm::mat4 view;

	Camera(GameObject* gameObject, Camera_Modes mode);
	Camera(std::string name, GameObject* gameObject, Camera_Modes mode);
	Camera(const char* name, GameObject* gameObject, Camera_Modes mode);
};

