#pragma once

#ifdef __cplusplus

extern "C" {
#endif // __cplusplus

typedef struct _UserCharacter {
	int CID;	//캐릭터 아이디
	int level;	//레벨
	int exp;	//경험치
	int hp;		//체력
	int attkPower;	//공격력
	int dfnsPower;	//방어력
} UserCharacter;

extern UserCharacter userCharacters[20]; //extern 꼭 해줘야 헤더오류 안남

void initUserCharacters();
void showUserCharacters();
void showUserCharacter(UserCharacter character);

#ifdef __cplusplus
}
#endif // __cplusplus

