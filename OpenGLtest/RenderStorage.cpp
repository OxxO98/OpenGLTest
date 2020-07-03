#include "RenderStorage.h"
#include "cTest.h"
#include "Game.h"
#include "gameObject.h"
#include "GMKL.h"

#include <string>
#include <iostream>

void RenderStorage::LoadRenderStorage(std::vector<RenderObj>* pageData, int page) {
	if (page == GMKL::MAIN_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "mainBackground", "none"));
		pageData->push_back(RenderObj(glm::vec2(70.0f, 590.0f), glm::vec2(285, 130), "stageButton", GMKL::makeRID(0, 0, 0)));
		pageData->push_back(RenderObj(glm::vec2(355.0f, 590.0f), glm::vec2(285, 130), "compositionButton", GMKL::makeRID(0, 0, 1)));
		pageData->push_back(RenderObj(glm::vec2(640.0f, 590.0f), glm::vec2(285, 130), "listButton", GMKL::makeRID(0, 0, 2)));
		pageData->push_back(RenderObj(glm::vec2(925.0f, 590.0f), glm::vec2(285, 130), "gattyaButton", GMKL::makeRID(0, 0, 3)));
	}
	if (page == GMKL::BATTLE_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0.0f, 0.0f), glm::vec2(1280, 720), "battleBackground", "none"));
		float xStart = 261.0f;
		float yStart = 265.0f;
		float xGap = 92.0f;
		float yGap = 55.0f;
		for (int i = 0; i < 9; i++) {
			if (getComposition(i) != -1) {
				int UCID = getUserCharacter(getComposition(i))->UCID;
				int CID = getUserCharacter(getComposition(i))->CID;
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110, 202), GMKL::toCIDString(CID), GMKL::toUCIDString(UCID)));
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
			pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110.0f, 202.0f), GMKL::toCIDString(CID), GMKL::toUCIDString(UCID)));
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
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(115, 115), "setButton", GMKL::toIDString(i, "setButton")));
			}
			else {
				int UCID = compCharacters[i];
				int CID = getUserCharacter(compCharacters[i])->CID;
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(115, 115), GMKL::toCIDString(CID), GMKL::toUCIDString(UCID)));
			}
			xStart += 115.0f;
			if ((i+1) % 3 == 0) {
				yStart += 115.0f;
				xStart = 132.0f;
			}
		}
	}
	if (page == GMKL::STAGE_PAGE) {
		pageData->push_back(RenderObj(glm::vec2(0, 0), glm::vec2(1280, 720), "stageBackground", "none"));
		pageData->push_back(RenderObj(glm::vec2(11.0f, 11.0f), glm::vec2(139, 46), "backwardButton", "backwardButton"));
		pageData->push_back(RenderObj(glm::vec2(455.0f, 484.0f), glm::vec2(147, 49), "stage1-1", "stage1-1"));
	}
}

void RenderStorage::UpdateRenderStorage(std::vector<RenderObj>* pageData, int page) {
	if (page == GMKL::BATTLE_PAGE) {
		float xStart = 261.0f;
		float yStart = 265.0f;
		float xGap = 92.0f;
		float yGap = 55.0f;
		for (int i = 0; i < 9; i++) {
			if (getComposition(i) != -1) {
				int UCID = getUserCharacter(getComposition(i))->UCID;
				int CID = getUserCharacter(getComposition(i))->CID;
				pageData->push_back(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110, 202), GMKL::toCIDString(CID), GMKL::toUCIDString(UCID)));
			}
			xStart += xGap;
			if ((i + 1) % 3 == 0) {
				xStart = 261.0f;
				xStart -= 57.0f * (i / 3 + 1);
				yStart += yGap;
			}
		}
	}
}

void RenderStorage::GetDataRenderStorage(void* data, void* externData, int type, int page) {
	if (page == GMKL::BATTLE_PAGE) {
		if (type == RenderStorage::MONSTER) {
			((std::vector<MonsterObject>*)data)[0].push_back(MonsterObject(&((Monster*)externData)[0], GameObject(RenderObj(glm::vec2(920.0f, 265.0f), glm::vec2(370, 188), "MID0", "MID0"))));
			((std::vector<MonsterObject>*)data)[1].push_back(MonsterObject(&((Monster*)externData)[1], GameObject(RenderObj(glm::vec2(920.0f, 320.0f), glm::vec2(370, 188), "MID0", "MID1"))));
			((std::vector<MonsterObject>*)data)[2].push_back(MonsterObject(&((Monster*)externData)[2], GameObject(RenderObj(glm::vec2(920.0f, 375.0f), glm::vec2(370, 188), "MID0", "MID2"))));
		}
		if (type == RenderStorage::CHARACTER) {
			float xStart = 261.0f;
			float yStart = 265.0f;
			float xGap = 92.0f;
			float yGap = 55.0f;
			for (int i = 0; i < 9; i++) {
				if (getComposition(i) != -1) {
					int UCID = getUserCharacter(getComposition(i))->UCID;
					int CID = getUserCharacter(getComposition(i))->CID;
					((std::vector<CharacterObject>*)data)->push_back(CharacterObject(getUserCharacter(getComposition(i)), GameObject(RenderObj(glm::vec2(xStart, yStart), glm::vec2(110, 202), GMKL::toCIDString(CID), GMKL::toUCIDString(UCID)))));
				}
				xStart += xGap;
				if ((i + 1) % 3 == 0) {
					xStart = 261.0f;
					xStart -= 57.0f * (i / 3 + 1);
					yStart += yGap;
				}
			}
		}
	}
}