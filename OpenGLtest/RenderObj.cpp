#include "RenderObj.h"

RenderObj::RenderObj(glm::vec2 pos, glm::vec2 size, std::string textureID, std::string objectID)
	:Position(pos), Size(size), TextureID(textureID), ObjectID(objectID) {}