#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <oxxoShader/Shader.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
bool defineVertexArray();
void windowSizeCallback(GLFWwindow* window, int width, int height);
void SCtoNDC(int len, int* SC, float* ret);
void setColortoNDC(int len, float* NDC, float* Color);
void setTextoNDC(int len, float* NDC, float* Tex);
void showVector(int len, float* vector);

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

int main(int argc, char** argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed" << std::endl;
		return -1;
	}
	Shader oxxoShader("../OpenGL/includes/oxxoShader/3.3.shader.vs", "../OpenGL/includes/oxxoShader/3.3.shader.fs");
	
	defineVertexArray();

	while (!glfwWindowShouldClose(window)) {
		//입력
		processInput(window);
		//렌더링 명령
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindTexture(GL_TEXTURE_2D, texture);
		oxxoShader.use();
		// 이벤트를 확인하고 버퍼 교체
		
		glfwSwapBuffers(window);
		glfwSetWindowSizeCallback(window, windowSizeCallback);
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VAO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
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
	
	if (SCR_WIDTH != width) {
		height = width * ratio;
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
		//std::cout << SCR_WIDTH << std::endl;
	}
	if (SCR_HEIGHT != height) {
		width = height / ratio;
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
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
		ret[i] = (float)(((float)SC[i]*2)/(float)SCR_HEIGHT-1) ;
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


bool defineVertexArray() {
	
	int scBox[] = {
		720, 720, 0,
		720, 0, 0,
		0, 0, 0,
		0, 720, 0
	};

	float scBoxc[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};

	float scBoxt[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	float vertices[32];

	SCtoNDC(12, scBox, vertices);
	showVector(3, vertices);
	setColortoNDC(12, vertices, scBoxc);
	showVector(6, vertices);
	setTextoNDC(24, vertices, scBoxt);
	showVector(8, vertices);

	unsigned int indices[] = {  // 0부터 시작한다는 것을 명심하세요!
		0, 1, 3,   // 첫 번째 삼각형
		1, 2, 3    // 두 번째 삼각형
	};

	unsigned int EBO;
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//위치
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//컬러
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attrubute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//set Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//image load
	int width, height, channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("img/asdf2-h.png", &width, &height, &channel, STBI_rgb_alpha);
	if (data) {
		std::cout << "일단 데이터는 가져옴\n" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "데이터 못가져옴" << std::endl;
	}
	stbi_image_free(data);


	//texture bind
	glBindTexture(GL_TEXTURE_2D, texture);

	//render shader
	glBindVertexArray(VAO);

	return true;
}