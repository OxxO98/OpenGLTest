#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "cTest.h"

//UserCharacter nchar;
UserCharacter userCharacters[3];
Monster stageMonster[3];
int compCharacters[9];
int procIndex;

void initUserCharacters() {
	userCharacters[0].CID = 1;
	userCharacters[0].UCID = 0;
	userCharacters[0].level = 1;
	userCharacters[0].exp = 0;
	userCharacters[0].hp = 100;
	userCharacters[0].attkPower = 100;
	userCharacters[0].attkVelocity = 200;
	userCharacters[0].coolTime = 0;
	userCharacters[0].dfnsPower = 150;
	userCharacters[0].depolyed = false;

	userCharacters[1].CID = 2;
	userCharacters[1].UCID = 1;
	userCharacters[1].level = 1;
	userCharacters[1].exp = 0;
	userCharacters[1].hp = 100;
	userCharacters[1].attkPower = 150;
	userCharacters[1].attkVelocity = 300;
	userCharacters[1].coolTime = 0;
	userCharacters[1].dfnsPower = 150;
	userCharacters[0].depolyed = false;

	userCharacters[2].CID = 3;
	userCharacters[2].UCID = 2;
	userCharacters[2].level = 1;
	userCharacters[2].exp = 0;
	userCharacters[2].hp = 100;
	userCharacters[2].attkPower = 200;
	userCharacters[2].attkVelocity = 400;
	userCharacters[2].coolTime = 0;
	userCharacters[2].dfnsPower = 150;
	userCharacters[0].depolyed = false;
}

void showUserCharacters() {
	for (int i = 0; i < 3; i++) {
		showUserCharacter(userCharacters[i]);
	}
}

void showUserCharacter(UserCharacter character) {
	printf("%d	", character.CID);
	printf("%d	", character.level);
	printf("%d	", character.exp);
	printf("%d	", character.attkPower);
	printf("%d\n", character.dfnsPower);
}

UserCharacter* getUserCharacter(int UCID) {
	for (int i = 0; i < sizeof(userCharacters) / sizeof(UserCharacter); i++) {
		if (userCharacters[i].UCID == UCID) {
			return &userCharacters[i];
		}
	}
	return &nchar;
}

void initMonster() {
	for (int i = 0; i < 3; i++) {
		stageMonster[i].MID = 0;
		stageMonster[i].UMID = i;
		stageMonster[i].hp = 2000;
		stageMonster[i].moveVelocity = -60;
		stageMonster[i].attkPower = 20;
		stageMonster[i].attkVelocity = 20;
		stageMonster[i].Destroyed = false;
	}
}

int getComposition(int index) {
	return compCharacters[index];
}

void setComposition(int index, int UCID) {
	if (getUserCharacter(UCID)->depolyed == true) {
		printf("이미 배치된 UCID입니다.\n");
		return;
	}
	compCharacters[index] = UCID;
	printf("setComp : UCID %d\n", UCID);
	getUserCharacter(UCID)->depolyed = true;
}

void procComposition(int index) {
	procIndex = index;
	printf("procComp : SetButton %d\n", index);
}

void initComposition() {
	for (int i = 0; i < 9; i++) {
		compCharacters[i] = -1;
	}
}

float aiMonster(int target, float dt) {
	return stageMonster[target].moveVelocity * dt;
}

int appointTarget(int UCID) {
	for (int i = 0; i < 9; i++) {
		if (compCharacters[i] == -1) {
			continue;
		}
		if (getUserCharacter(compCharacters[i])->UCID == UCID) {
			if (0 <= i && i <= 2) {
				return 0;
			}
			if (3 <= i && i <= 5) {
				return 1;
			}
			if (6 <= i && i <= 8) {
				return 2;
			}
		}
	}
}