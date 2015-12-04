#include "GamePlayUI.h"
#include <DxLib.h>
#include "Keyboard.h"

GamePlayUI::GamePlayUI(DataManager *_DataManager)
{
	m_DataManager = _DataManager;
}

GamePlayUI::~GamePlayUI()
{
}

void GamePlayUI::init()
{
	EnergieIcon_x = 0;
	EnergieIcon_y = 0;
	EnergieCage_x = 96;
	EnergieCage_y = 48;
	Heart_x = 128;
	Heart_y = 8;
	Energie = 0;
	WordSize = 96;
	EnergieFlg = TRUE;
}

void GamePlayUI::updata()
{
	/*if (EnergieFlg == TRUE)
	{
		if (Key_Get(KEY_INPUT_R) != 0){
			Energie++;
			WordSize += 4;
		}
		else{
			Energie--;
			WordSize -= 4;
		}
		if (Energie < 0){ Energie = 0; }
		if (Energie > 320){ Energie = 320; EnergieFlg = FALSE; }
	}
	else{
		Energie--;
		WordSize -= 4;
		if (Energie < 0){
			Energie = 0;
			EnergieFlg = TRUE;
		}
	}

	if (WordSize < 96){ WordSize = 96; }
	if (WordSize > 256){ WordSize = 256; }*/
}

void GamePlayUI::draw()
{
	if (Key_Get(KEY_INPUT_E) != 0)
	{
		DrawGraph(EnergieIcon_x, EnergieIcon_y, m_DataManager->EnergieIcon, TRUE);
		SetDrawBright(0, 0, 0);
		DrawGraph(EnergieCage_x, EnergieCage_y, m_DataManager->Energie, TRUE);
		SetDrawBright(255, 255, 255);

		DrawRectGraph(EnergieCage_x, EnergieCage_y, 0, 0, 320 - Energie, 32, m_DataManager->Energie, TRUE, FALSE);

		for (int i = 0; i < 4; i++)
		{
			DrawGraph(Heart_x + i * 64, Heart_y, m_DataManager->Heart, TRUE);
		}
	}


	//CreateMaskScreen();
	//DrawMask(0, 0, m_DataManager->Word, DX_MASKTRANS_NONE);
	//DrawGraph(0,0,m_DataManager->Dark,FALSE);
	////DrawBox(0, 0, 1280, 720, RGB(0, 0, 0), TRUE);
	//DeleteMaskScreen();
}
