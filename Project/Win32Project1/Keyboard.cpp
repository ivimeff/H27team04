#include "DxLib.h"

static int m_Key[256];	//�L�[�̓��͏�Ԋi�[�p�ϐ�

//�L�[�̓��͏�ԍX�V
void Key_Update(){
	char tmpKey[256];			//���݂̃L�[�̓��͏�Ԃ��i�[
	GetHitKeyStateAll(tmpKey);	//�S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++){
		if (tmpKey[i] != 0){
			m_Key[i]++;
		}
		else{
			m_Key[i] = 0;
		}
	}
}

//KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Key_Get(int KeyCode){
	return m_Key[KeyCode];	//KeyCode�̓��͏�Ԃ�Ԃ�
}