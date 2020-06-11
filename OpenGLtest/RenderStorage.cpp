#include "RenderStorage.h"
#include "cTest.h"

#include <string>
#include <iostream>

void RenderStorage::LoadRenderStorage(std::vector<RenderObj>* pageData, std::string page) {
	if (page == "MainMenu") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "mainBackground", "mainBackground"));
		pageData->push_back(RenderObj(glm::vec2(758.0f, 259.0f), glm::vec2(450, 179), "fight", "fight"));
		pageData->push_back(RenderObj(glm::vec2(780.0f, 457.0f), glm::vec2(225, 105), "set", "set"));
		pageData->push_back(RenderObj(glm::vec2(968.0f, 528.0f), glm::vec2(225, 105), "event", "event"));
	}
	if (page == "BattlePage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "battleBackground"));
		pageData->push_back(RenderObj(glm::vec2(146.0f, 382.0f), glm::vec2(110, 202), "CID1", "character"));
		pageData->push_back(RenderObj(glm::vec2(459.0f, 264.0f), glm::vec2(110, 202), "CID1", "character"));
	}
	if (page == "CharactersPage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "battleBackground"));
		float xStart = 0.0f;
		float yStart = 0.0f;
		for (int i = 0; i < 20; i++) {
			int CID = userCharacters[i].CID;
			std::string CIDstr = "CID" + std::to_string(CID);
			std::cout << CIDstr << std::endl;
			pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110.0f, 202.0f), CIDstr, "character"));
			xStart += 110.0f;
			if (i % 5 == 1) {
				xStart = 0.0f;
				yStart += 202.0f;
			}
		}
	}
}