#pragma once

#ifdef __cplusplus

extern "C" {
#endif // __cplusplus

typedef struct _UserCharacter {
	int CID;	//캐릭터 아이디
	int UCID;
	int level;	//레벨
	int exp;	//경험치
	int hp;		//체력
	int attkPower;	//공격력
	int dfnsPower;	//방어력
} UserCharacter;

extern UserCharacter userCharacters[3]; //extern 꼭 해줘야 헤더오류 안남
extern int compCharacters[9];
extern int procIndex;
static const UserCharacter nchar;

void initUserCharacters();
void showUserCharacters();
void showUserCharacter(UserCharacter character);
UserCharacter getUserCharacter(int UCID);
int getComposition(int index);
void setComposition(int index, int UCID);
void procComposition(int index);
void initComposition();

#ifdef __cplusplus
}
#endif // __cplusplus

