#pragma once

#ifdef __cplusplus

extern "C" {
#endif // __cplusplus

typedef struct _UserCharacter {
	int CID;	//ĳ���� ���̵�
	int level;	//����
	int exp;	//����ġ
	int hp;		//ü��
	int attkPower;	//���ݷ�
	int dfnsPower;	//����
} UserCharacter;

extern UserCharacter userCharacters[20]; //extern �� ����� ������� �ȳ�

void initUserCharacters();
void showUserCharacters();
void showUserCharacter(UserCharacter character);

#ifdef __cplusplus
}
#endif // __cplusplus

