#include "GameTitle.h"
#include <stdio.h>
#include <DxLib.h>

GameTitle::GameTitle(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad) : Scene(_DataManager, _Renderer, _GamePad) {}

GameTitle::~GameTitle()
{

}

void GameTitle::init()
{
	end = false;
	title_x = 0;
	title_y = 0;
}

void GameTitle::update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}
}

void GameTitle::draw()
{
	m_Renderer->drawTexture(m_pDataManager->title, title_x, title_y);
}

GAME_MODE GameTitle::nextScene()
{
	return GAME_MODE_GAMEMENU;
}

GAME_MODE GameTitle::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMEMENU;
}