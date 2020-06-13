#include "RenderStorage.h"
#include "cTest.h"

#include <string>
#include <iostream>

void RenderStorage::LoadRenderStorage(std::vector<RenderObj>* pageData, std::string page) {
	if (page == "MainMenu") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "mainBackground", "mainBackground"));
		pageData->push_back(RenderObj(glm::vec2(758.0f, 259.0f), glm::vec2(450, 179), "fight", "fight"));
		pageData->push_back(RenderObj(glm::vec2(780.0f, 457.0f), glm::vec2(225, 105), "list", "list"));
		pageData->push_back(RenderObj(glm::vec2(968.0f, 528.0f), glm::vec2(225, 105), "set", "set"));
	}
	if (page == "BattlePage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "battleBackground"));
		pageData->push_back(RenderObj(glm::vec2(146.0f, 382.0f), glm::vec2(110, 202), "CID1", "character"));
		pageData->push_back(RenderObj(glm::vec2(459.0f, 264.0f), glm::vec2(110, 202), "CID1", "character"));
	}
	if (page == "CharactersPage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "listBackground", "listBackground"));
		pageData->push_back(RenderObj(glm::vec2(11.0f, 11.0f), glm::vec2(139, 46), "backwardButton", "backwardButton"));
		float xStart = 40.0f;
		float yStart = 63.0f;
		for (int i = 0; i < 3; i++) {
			int CID = userCharacters[i].CID;
			int UCID = userCharacters[i].UCID;
			std::string CIDstr = "CID" + std::to_string(CID);
			std::string UCIDstr = "UCID" + std::to_string(UCID);
			std::cout << UCIDstr << std::endl;
			pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110.0f, 202.0f), CIDstr, UCIDstr));
			xStart += 110.0f;
		}
	}
	if (page == "SettingPage") {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "listBackground", "listBackground"));
		pageData->push_back(RenderObj(glm::vec2(11.0f, 11.0f), glm::vec2(139, 46), "backwardButton", "backwardButton"));
		float xStart = 132.0f;
		float yStart = 165.0f;
		for (int i = 0; i < 9; i++) {
			if (compCharacters[i] == -1) {
				std::string RIDstr = "setButton" + std::to_string(i);
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(115, 115), "setButton", RIDstr));
			}
			else {
				std::string CIDstr = "CID" + std::to_string(compCharacters[i]);
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110, 202), CIDstr, "character"));
			}
			xStart += 115.0f;
			if ((i+1) % 3 == 0) {
				yStart += 115.0f;
				xStart = 132.0f;
			}
		}
	}
}