#include "RenderStorage.h"

void RenderStorage::LoadRenderStorage(std::vector<RenderObj>* pageData, std::string page) {
	if (page == "MainMenu") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "mainBackground", "mainBackground"));
		pageData->push_back(RenderObj(glm::vec2(758.0f, 259.0f), glm::vec2(450, 179), "fight", "fight"));
		pageData->push_back(RenderObj(glm::vec2(780.0f, 457.0f), glm::vec2(225, 105), "set", "set"));
		pageData->push_back(RenderObj(glm::vec2(968.0f, 528.0f), glm::vec2(225, 105), "event", "event"));
	}
	if (page == "BattlePage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "battleBackground"));
		pageData->push_back(RenderObj(glm::vec2(146.0f, 382.0f), glm::vec2(110, 202), "character", "character"));
		pageData->push_back(RenderObj(glm::vec2(459.0f, 264.0f), glm::vec2(110, 202), "character", "character"));
	}
}