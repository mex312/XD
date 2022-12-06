#define GLEW_STATIC
#include <stdio.h>
#include <cmath>
#include "GLShader.h"
#include "GLCamera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Core.h"
#include "Camera.h"
#include "CameraController.h"
#include "3DComponents.h"

GLFWwindow* window;

GLfloat sensitivity = 0.2f;

GLfloat deltaTime;

GLCamera camera;

bool keys1[1024] = { false };
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	printf("KEY PRESSED\n");
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (action == GLFW_PRESS) {
		keys1[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keys1[key] = false;
	}
}


void initVBO(GLuint VAO, GLuint VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void updateStaticVBO(GLuint VAO, GLuint VBO, GLfloat* vertices, GLuint arraySize) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_ARRAY_BUFFER, arraySize, vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


int init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "NAME", nullptr, nullptr);
	if (window == nullptr) {
		printf("Failed to create window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetKeyCallback(window, Input::key_callback);
	glfwSetCursorPosCallback(window, Input::mouse_callback);
	glfwSetScrollCallback(window, Input::scroll_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glAlphaFunc(GL_GREATER, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//glDisable(GL_CULL_FACE);

	Core::initCore();

	return 0;
}


int main() {
	if (init() == -1) return -1;

	//long long i = 0;
	/*while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		Core::updateCore();
		printf("Iteration %016lld started...\n", i);
		printf("Delta time: %llf\n", Time::deltaTime());
		GameObject* obj1 = new GameObject("name1");
		GameObject* obj2 = new GameObject("name2");
		GameObject* obj3 = new GameObject("name3");
		//Component* comp1 = new Component(obj1);
		//printf("%s\n", comp1->gameObject->name.c_str());
		for (auto component : obj1->components) {
			//printf("%s\n", component->name.c_str());
		}
		obj2->transform.setParent(&(obj1->transform));
		obj3->transform.setParent(&(obj1->transform));
		std::string name1 = obj2->parent->name;
		//printf("%s\n", name1.c_str());
		int it = 1;
		for (auto child : obj1->children) {
			//printf("Child %3d name: %s\n", it, child->name.c_str());
			it++;
		}
		//printf("Iteration %016llx finished!\n", i);
		i++;
		delete obj1;
	}*/

	GLShader shader("shader.vert", "shader.frag");


	GLfloat vertices[504] = { 0 };
	CubeModel cube1 = CubeModel();
	CubeModel cube2 = CubeModel();
	cube2.setSideTexture(CubeModel::FRONT, vec2(0, 1));
	cube1.writeToVertexArray(vertices, 0, vec3(0, 0, 0));
	cube2.writeToVertexArray(vertices, 252, vec3(0, 1, 0));
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	initVBO(VAO, VBO);
	updateStaticVBO(VAO, VBO, vertices, sizeof(GLfloat) * 504);


	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	int width, height;
	unsigned char* image = SOIL_load_image("Textures.png", &width, &height, 0, SOIL_LOAD_RGBA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	glm::mat4 model(1);
	//model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	GLfloat lastTime = glfwGetTime();

	GameObject cameraObject("Main Camera Object");
	Camera camera("Main Camera", &cameraObject, PERSPECTIVE);
	CameraController cameraController("Camera Controller", &cameraObject);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		Core::updateCore();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		GLfloat time = glfwGetTime();
		deltaTime = time - lastTime;
		//GLuint customColor = glGetUniformLocation(shader.program, "customColor");
		GLuint u_view= glGetUniformLocation(shader.program, "u_view");
		GLuint u_model = glGetUniformLocation(shader.program, "u_model");
		GLuint u_texNumInv = glGetUniformLocation(shader.program, "u_texNumInv");

		shader.use();

		//glUniform4f(customColor, 0, 0, 0, 1);
		glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(camera.view));
		glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2f(u_texNumInv, 1.0f / 1.0f, 1.0f / 3.0f);

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 7);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		lastTime = time;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}