#include "DxLib.h"

static int m_Key[256];	//キーの入力状態格納用変数

//キーの入力状態更新
void Key_Update(){
	char tmpKey[256];			//現在のキーの入力状態を格納
	GetHitKeyStateAll(tmpKey);	//全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++){
		if (tmpKey[i] != 0){
			m_Key[i]++;
		}
		else{
			m_Key[i] = 0;
		}
	}
}

//KeyCodeのキーの入力状態を取得する
int Key_Get(int KeyCode){
	return m_Key[KeyCode];	//KeyCodeの入力状態を返す
}