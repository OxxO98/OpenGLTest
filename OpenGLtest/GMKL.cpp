#include "GMKL.h"
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