#include <string.h>
#include <stdio.h>
#include "cTest.h"

UserCharacter userCharacters[3];
int compCharacters[9];
int procIndex;

void initUserCharacters() {
	userCharacters[0].CID = 1;
	userCharacters[0].UCID = 0;
	userCharacters[0].level = 1;
	userCharacters[0].exp = 0;
	userCharacters[0].hp = 100;
	userCharacters[0].attkPower = 200;
	userCharacters[0].dfnsPower = 150;

	userCharacters[1].CID = 2;
	userCharacters[1].UCID = 1;
	userCharacters[1].level = 1;
	userCharacters[1].exp = 0;
	userCharacters[1].hp = 100;
	userCharacters[1].attkPower = 200;
	userCharacters[1].dfnsPower = 150;

	userCharacters[2].CID = 3;
	userCharacters[2].UCID = 2;
	userCharacters[2].level = 1;
	userCharacters[2].exp = 0;
	userCharacters[2].hp = 100;
	userCharacters[2].attkPower = 200;
	userCharacters[2].dfnsPower = 150;
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

void setComposition(int index, int UCID) {
	compCharacters[index] = UCID;
	printf("%d", UCID);
}

void procComposition(int index) {
	procIndex = index;
	printf("%d", index);
}

void initComposition() {
	for (int i = 0; i < 9; i++) {
		compCharacters[i] = -1;
	}
}