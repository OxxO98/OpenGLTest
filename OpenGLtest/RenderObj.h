#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class RenderObj
{
public:
	//member
	glm::vec2 Position;
	glm::vec2 Size;
	std::string TextureID;
	std::string ObjectID;
	//constructor
	RenderObj(glm::vec2 pos, glm::vec2 size, std::string textureID, std::string objectID);
};

