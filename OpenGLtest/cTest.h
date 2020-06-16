#pragma once

#ifdef __cplusplus

extern "C" {
#endif // __cplusplus

typedef struct _UserCharacter {
	int CID;	//ĳ���� ���̵�
	int UCID;
	int level;	//����
	int exp;	//����ġ
	int hp;		//ü��
	int attkPower;	//���ݷ�
	int dfnsPower;	//����
} UserCharacter;

extern UserCharacter userCharacters[3]; //extern �� ����� ������� �ȳ�
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

