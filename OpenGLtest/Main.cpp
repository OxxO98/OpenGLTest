#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "ResourceManager.h"
#include "Game.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void processInput(GLFWwindow* window);

void windowSizeCallback(GLFWwindow* window, int width, int height);

void SCtoNDC(int len, int* SC, float* ret);
void setColortoNDC(int len, float* NDC, float* Color);
void setTextoNDC(int len, float* NDC, float* Tex);
void showVector(int len, float* vector);

unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char** argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (window == NULL) {
		std::cout << "Failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed" << std::endl;
		return -1;
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Breakout.Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Breakout.State = GAME_MENU;

	while (!glfwWindowShouldClose(window)) {
		//calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		//manage user input
		Breakout.ProcessInput(deltaTime);
		
		//update game state
		Breakout.Update(deltaTime);
		
		//render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);
		glfwSetWindowSizeCallback(window, windowSizeCallback);
	}
	
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = false;
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	float ratio = 0.5625;
	glfwGetWindowSize(window, &width, &height);
	
	if (SCREEN_WIDTH != width) {
		height = width * ratio;
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		//std::cout << SCR_WIDTH << std::endl;
	}
	if (SCREEN_HEIGHT != height) {
		width = height / ratio;
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		//std::cout << SCR_WIDTH << std::endl;
	}
	glfwSetWindowSize(window, width, height);
}

void showVector(int len,  float* vector) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < len; j++) {
			std::cout << vector[i * len + j] << "\t";
		}
		std::cout << "\n";
	}
}

void SCtoNDC(int len, int* SC, float* ret) {
	for (int i = 0; i < len; i++) {
		ret[i] = (float)(((float)SC[i]*2)/(float)SCREEN_HEIGHT -1) ;
	}
}

void setColortoNDC(int len, float* NDC, float* Color) {
	for (int i = 3; i >= 0; i--) {
		NDC[i * 6 + 2] = NDC[i * 3 + 2];
		NDC[i * 6 + 1] = NDC[i * 3 + 1];
		NDC[i * 6] = NDC[i * 3];

		NDC[i * 6 + 3] = Color[i * 3];
		NDC[i * 6 + 4] = Color[i * 3 + 1];
		NDC[i * 6 + 5] = Color[i * 3 + 2];
	}
}

void setTextoNDC(int len, float* NDC, float* Tex) {
	for (int i = 3; i >= 0; i--) {
		NDC[i * 8 + 5] = NDC[i * 6 + 5];
		NDC[i * 8 + 4] = NDC[i * 6 + 4];
		NDC[i * 8 + 3] = NDC[i * 6 + 3];
		NDC[i * 8 + 2] = NDC[i * 6 + 2];
		NDC[i * 8 + 1] = NDC[i * 6 + 1];
		NDC[i * 8] = NDC[i * 6];

		NDC[i * 8 + 6] = Tex[i * 2];
		NDC[i * 8 + 7] = Tex[i * 2 + 1];
	}
}