#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "RenderObj.h"

class RenderStorage {
public:
	enum {
		MONSTER,
		CHARACTER,
		EFFECT
	};

	static void LoadRenderStorage(std::vector<RenderObj>* pageData, int page);
	static void UpdateRenderStorage(std::vector<RenderObj>* pagedata, int page);

	static void GetDataRenderStorage(void* data, void* externData, int type, int page);
};