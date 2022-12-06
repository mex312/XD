#include "CameraController.h"

CameraController::CameraController(GameObject* gameObject) : Behavior("New Behavior", gameObject)
{}

CameraController::CameraController(std::string& name, GameObject* gameObject) : Behavior(name, gameObject)
{}

CameraController::CameraController(const char* name, GameObject* gameObject) : Behavior(name, gameObject)
{}