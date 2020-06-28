#ifndef GMKL_H
#define GMKL_H
#include <string>
#include <queue>
#include <vector>
#include "gameObject.h"

class GMKL
{
public:
	//enum Pages�� ���� ������� �־������
	enum GamePageName {
        MAIN_PAGE,
        LIST_PAGE,
        STAGE_PAGE,
        COMPOSITION_PAGE,
        BATTLE_PAGE
    };
    static std::queue<std::string> Event;

    static std::string toUCIDString(int RID);
    static std::string toCIDString(int TID);
    static int toUCID(std::string RIDstr);
    static int toCID(std::string TIDstr);
    static int toID(std::string RIDstr, std::string findStr); //����+���ڿ��� ���ڸ� ��ȯ
    static std::string toIDString(int ID, std::string IDstr);
    static std::string makeRID(int pageNum, int groupNum, int buttonNum);

    static GameObject* getGameObject(std::vector<GameObject> *gameObjs, std::string ID);

    static void loadBackground();
    static void loadResource();
    static void loadCharacter();

private:
	GMKL() {}
};

#endif