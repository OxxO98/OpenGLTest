#include "RenderStorage.h"
#include "cTest.h"
#include "Game.h"
#include "GMKL.h"

#include <string>
#include <iostream>

void RenderStorage::LoadRenderStorage(std::vector<RenderObj>* pageData, int page) {
	if (page == GMKL::MAIN_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "mainBackground", "none"));
		pageData->push_back(RenderObj(glm::vec2(758.0f, 259.0f), glm::vec2(450, 179), "fight", "fight"));
		pageData->push_back(RenderObj(glm::vec2(780.0f, 457.0f), glm::vec2(225, 105), "list", "list"));
		pageData->push_back(RenderObj(glm::vec2(968.0f, 528.0f), glm::vec2(225, 105), "set", "set"));
	}
	if (page == GMKL::BATTLE_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "none"));
		float xStart = 261.0f;
		float yStart = 265.0f;
		float xGap = 92.0f;
		float yGap = 55.0f;
		for (int i = 0; i < 9; i++) {
			if (getComposition(i) != -1) {
				int UCID = getUserCharacter(getComposition(i)).UCID;
				int CID = getUserCharacter(getComposition(i)).CID;
				std::string UCIDstr = "UCID" + std::to_string(UCID);
				std::string CIDstr = "CID" + std::to_string(CID);
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110, 202), CIDstr, UCIDstr));
			}
			xStart += xGap;
			if ((i + 1) % 3 == 0) {
				xStart = 261.0f;
				xStart -= 57.0f * (i/3 +1);
				yStart += yGap;
			}
		}
	}
	if (page == GMKL::LIST_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "listBackground", "none"));
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
	if (page == GMKL::COMPOSITION_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "listBackground", "none"));
		pageData->push_back(RenderObj(glm::vec2(11.0f, 11.0f), glm::vec2(139, 46), "backwardButton", "backwardButton"));
		float xStart = 132.0f;
		float yStart = 165.0f;
		for (int i = 0; i < 9; i++) {
			if (compCharacters[i] == -1) {
				std::string RIDstr = "setButton" + std::to_string(i);
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(115, 115), "setButton", RIDstr));
			}
			else {
				std::string UCIDstr = "UCID" + std::to_string(compCharacters[i]);
				std::string CIDstr = "CID" + std::to_string(getUserCharacter(compCharacters[i]).CID);
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(115, 115), CIDstr, UCIDstr));
			}
			xStart += 115.0f;
			if ((i+1) % 3 == 0) {
				yStart += 115.0f;
				xStart = 132.0f;
			}
		}
	}
}