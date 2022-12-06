#include "Input.h"


static float mouseSensitivity = 1.0f;
static float scrollSensitivity = 1.0f;


bool keys[1024] = { false };
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (action == GLFW_PRESS) {
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

glm::vec2 lastMousePos(0);
glm::vec2 nowMousePos(0);
glm::vec2 deltaMousePos(0);
bool mouseMoved = false;
void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!mouseMoved) {
		lastMousePos = glm::vec2(xpos, ypos);
		mouseMoved = true;
	}
	nowMousePos = glm::vec2(xpos, ypos);
}

glm::vec2 nowScroll(0);
glm::vec2 deltaScroll(0);
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	nowScroll += glm::vec2(xoffset, yoffset);
}

void Input::updateInput()
{
	deltaMousePos = (nowMousePos - lastMousePos) * mouseSensitivity;
	lastMousePos = nowMousePos;

	deltaScroll = nowScroll * scrollSensitivity;
	nowScroll = glm::vec2(0);
}

void Input::initInput() 
{
	mouseSensitivity = 1.0f;
	scrollSensitivity = 1.0f;
}

glm::vec2 Input::getMouseInput()
{
	return deltaMousePos;
}

bool Input::getKey(int key)
{
	return keys[key];
}
