#pragma once
#include "Behavior.h"
#include "GameObject.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include "Time.h"
#include "Input.h"

class CameraController : public Behavior
{
public:
	float xRot = 0;
	float yRot = 0;

	void Update() {
		xRot += Input::getMouseInput().y / 100;
		yRot += Input::getMouseInput().x / 100;
		gameObject->transform.rotation = glm::normalize( glm::quat(glm::vec3(xRot, 0, 0)) * glm::quat(glm::vec3(0, yRot, 0)) );
		//gameObject->transform.rotation = glm::quat(glm::vec3(xRot, yRot, 0));
		
		glm::vec3 deltaPos = glm::vec3(0, 0, 0);
		if (Input::getKey(GLFW_KEY_D)) {
			deltaPos.x++;
		}
		if (Input::getKey(GLFW_KEY_A)) {
			deltaPos.x--;
		}
		if (Input::getKey(GLFW_KEY_W)) {
			deltaPos.z--;
		}
		if (Input::getKey(GLFW_KEY_S)) {
			deltaPos.z++;
		}
		if (Input::getKey(GLFW_KEY_SPACE)) {
			deltaPos.y++;
		}
		if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) {
			deltaPos.y--;
		}
		gameObject->transform.position += (deltaPos * (float)Time::deltaTime()) * gameObject->transform.rotation;
	}

	CameraController(GameObject* gameObject);
	CameraController(std::string& name, GameObject* gameObject);
	CameraController(const char* name, GameObject* gameObject);
};

