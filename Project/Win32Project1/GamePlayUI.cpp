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
	EnergieIcon_x = 16;
	EnergieIcon_y = 0;
	EnergieCage_x = 96;
	EnergieCage_y = 48;
	Heart_x = 128;
	Heart_y = 8;
	WordSize = 96;
	EnergieFlg = TRUE;
}

void GamePlayUI::updata()
{
	//printf("%d", PlayerDamageFlg);
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
}
void GamePlayUI::SetViewSize(int _Energie)
{
	Energie = _Energie;
}

bool GamePlayUI::SetPlayerDamageFlg(bool _PlayerDamageFlg)
{
	PlayerDamageFlg = _PlayerDamageFlg;
	return PlayerDamageFlg;
}