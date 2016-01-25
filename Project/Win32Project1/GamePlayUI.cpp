#include "GamePlayUI.h"
#include <DxLib.h>
#include "Keyboard.h"

GamePlayUI::GamePlayUI(Renderer *_Renderer,GamePad *_gamepad)
{
	m_Renderer = _Renderer;
	m_gamepad = _gamepad;
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
	HeartMax = 4;
	Heart = HeartMax;
	WordSize = 96;
	EnergieFlg = TRUE;
	StarTime = 0;
	GameOverFlg = false;
}

void GamePlayUI::updata()
{
	StarTime--;
	if (StarTime < 0){
		StarTime = 0;
		if (PlayerDamageFlg == TRUE)
		{
			Heart--;
			StarTime = 200;
		}
	}
	if (Heart < 1)
	{ 
		Heart = 0; 
		GameOverFlg = TRUE;
	}
	printf("%d", StarTime);
}

void GamePlayUI::draw()
{
	//パッドのRボタン
#ifdef _DEBUG
	if (Key_Get(KEY_INPUT_E) != 0 || m_gamepad->getInputButton(PAD_INPUT_6))
#endif
	{
		m_Renderer->drawTexture("EnergyIcon", EnergieIcon_x, EnergieIcon_y);
		SetDrawBright(0, 0, 0);
		m_Renderer->drawTexture("Energy", EnergieCage_x, EnergieCage_y);
		SetDrawBright(255, 255, 255);
		

		m_Renderer->drawTextureRect("Energy", EnergieCage_x, EnergieCage_y, 0, 0, 320 - Energie, 32);

		for (int i = 0; i < Heart; i++)
		{
			m_Renderer->drawTexture("Heart", Heart_x + i * 64, Heart_y);
		}
	}
}
void GamePlayUI::SetViewSize(int _Energie)
{
	Energie = _Energie;
}

void GamePlayUI::SetPlayerDamageFlg(bool _PlayerDamageFlg)
{
	//printf("%d", PlayerDamageFlg);
	PlayerDamageFlg = _PlayerDamageFlg;
}