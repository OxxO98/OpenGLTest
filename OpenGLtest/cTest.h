#pragma once

#ifdef __cplusplus

extern "C" {
#endif // __cplusplus

#include <stdbool.h>
typedef struct _UserCharacter {
	int CID;	//ĳ���� ���̵�
	int UCID;
	int level;	//����
	int exp;	//����ġ
	int hp;		//ü��
	int attkPower;	//���ݷ�
	int attkVelocity;
	float coolTime;
	int dfnsPower;	//����
} UserCharacter;

typedef struct _Monster {
	int MID;
	int UMID;
	int hp;
	int moveVelocity;
	int attkPower;
	int attkVelocity;
	bool Destroyed;
} Monster;

extern UserCharacter userCharacters[3]; //extern �� ����� ������� �ȳ�
extern int compCharacters[9];
extern int procIndex;
static const UserCharacter nchar;
extern Monster stageMonster[3];

void initUserCharacters();
void showUserCharacters();
void showUserCharacter(UserCharacter character);
UserCharacter* getUserCharacter(int UCID);

int getComposition(int index);
void setComposition(int index, int UCID);
void procComposition(int index);
void initComposition();

void initMonster();
float aiMonster(int target, float dt);
int appointTarget(int UCID);

#ifdef __cplusplus
}
#endif // __cplusplus

