#include "GMKL.h"
#include "ResourceManager.h"
#include "gameObject.h"
#include <iostream>
#include <string>

std::queue<std::string> GMKL::Event;

std::string GMKL::toUCIDString(int RID) {
	return "UCID" + std::to_string(RID);
}

std::string GMKL::toCIDString(int TID) {
	return "CID" + std::to_string(TID);
}

int GMKL::toUCID(std::string RIDstr) {
	if (int pos = RIDstr.find("UCID") != std::string::npos) {
		return std::stoi(RIDstr.substr(pos + 3));
	}
	return -1;
}

int GMKL::toCID(std::string TIDstr) {
	if (int pos = TIDstr.find("CID") != std::string::npos) {
		return std::stoi(TIDstr.substr(pos + 2));
	}
	return -1;
}

int GMKL::toID(std::string RIDstr, std::string findStr) {
	if (int pos = RIDstr.find(findStr) != std::string::npos) {
		return std::stoi(RIDstr.substr(pos + findStr.size() - 1));
	}
	return -1;
}

std::string GMKL::toIDString(int ID, std::string IDstr) {
	return IDstr + std::to_string(ID);
}

std::string GMKL::makeRID(int pageNum, int groupNum, int buttonNum) {
	std::string pageStr;
	std::string groupStr;
	std::string buttonStr;
	
	if (pageNum > 9) {
		pageStr = std::to_string(pageNum);
	}
	else {
		pageStr = "0" + std::to_string(pageNum);
	}

	if (pageNum > 9) {
		groupStr = std::to_string(groupNum);
	}
	else {
		groupStr = "0" + std::to_string(groupNum);
	}
	buttonStr = std::to_string(buttonNum);

	return "RID" + pageStr + groupStr + buttonStr;
}

GameObject* GMKL::getGameObject(std::vector<GameObject>* gameObjs, std::string ID) {
	for (int i = 0; i < gameObjs->size(); i++) {
		GameObject* elem = &gameObjs->at(i);
		if (elem->ID == ID) {
			//std::cout << elem->ID << std::endl;
			return elem;
		}
	}
	std::cout << "ERROR:getGameObject:undefined" << std::endl;
	return NULL;
}

void GMKL::loadBackground() {
	ResourceManager::LoadTexture("img/Background/MainBackground.png", true, "mainBackground");
	ResourceManager::LoadTexture("img/Background/CombatBackground.png", false, "battleBackground");
	ResourceManager::LoadTexture("img/Background/OperatorBackground.png", false, "listBackground");
	ResourceManager::LoadTexture("img/Background/StageBackground.png", false, "stageBackground");
}

void GMKL::loadResource() {
	ResourceManager::LoadTexture("img/Resource/Combat.png", true, "stageButton");
	ResourceManager::LoadTexture("img/Resource/Sqauds.png", true, "compositionButton");
	ResourceManager::LoadTexture("img/Resource/Operator.png", true, "listButton");
	ResourceManager::LoadTexture("img/Resource/Recruitment.png", true, "gattyaButton");

	ResourceManager::LoadTexture("img/Resource/backwardButton.png", true, "backwardButton");
	ResourceManager::LoadTexture("img/Resource/setButton.png", true, "setButton");
	ResourceManager::LoadTexture("img/Resource/stage1-1.png", true, "stage1-1");
}

void GMKL::loadCharacter() {
	ResourceManager::LoadTexture("img/CID/CID0.png", true, "CID0");
	ResourceManager::LoadTexture("img/CID/CID1.png", true, "CID1");
	ResourceManager::LoadTexture("img/CID/CID2.png", true, "CID2");
	ResourceManager::LoadTexture("img/CID/CID3.png", true, "CID3");

	ResourceManager::LoadTexture("img/CID/MID0.png", true, "MID0");
}