#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "RenderObj.h"

class RenderStorage {
public:
	static void LoadRenderStorage(std::vector<RenderObj>* pageData, int page);
};