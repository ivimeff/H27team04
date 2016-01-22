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
	WordSize = 96;
	EnergieFlg = TRUE;
}

void GamePlayUI::updata()
{
	//printf("%d", PlayerDamageFlg);
}

void GamePlayUI::draw()
{
	//パッドのRボタン
	if (Key_Get(KEY_INPUT_E) != 0 || m_gamepad->getInputButton(PAD_INPUT_6))
	{
		m_Renderer->drawTexture("EnergyIcon", EnergieIcon_x, EnergieIcon_y);
		SetDrawBright(0, 0, 0);
		m_Renderer->drawTexture("Energy", EnergieCage_x, EnergieCage_y);
		SetDrawBright(255, 255, 255);
		

		m_Renderer->drawTextureRect("Energy", EnergieCage_x, EnergieCage_y, 0, 0, 320 - Energie, 32);

		for (int i = 0; i < 4; i++)
		{
			m_Renderer->drawTexture("Heart", Heart_x + i * 64, Heart_y);
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