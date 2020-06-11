#include <string.h>
#include <stdio.h>
#include "cTest.h"

UserCharacter userCharacters[20];

void initUserCharacters() {
	for (int i = 0; i < 20; i++) {
		userCharacters[i].CID = 1;
		userCharacters[i].level = 20;
		userCharacters[i].exp = 30;
		userCharacters[i].attkPower = 100;
		userCharacters[i].dfnsPower = 150;
	}
}

void showUserCharacters() {
	for (int i = 0; i < 20; i++) {
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