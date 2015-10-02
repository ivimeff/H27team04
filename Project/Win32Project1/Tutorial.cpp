#include "Tutorial.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial::Tutorial(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad) : Scene(_DataManager, _Renderer, _GamePad)
{

}

Tutorial::~Tutorial()
{

}

void Tutorial::init()
{
	end = false;
	tuto_x = 0;
	tuto_y = 0;
}

void Tutorial::update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}
}

void Tutorial::draw()
{
	m_Renderer->drawTexture(m_pDataManager->tuto, tuto_x, tuto_y);
}

GAME_MODE Tutorial::nextScene()
{
	return GAME_MODE_GAMEMENU;
}

GAME_MODE Tutorial::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMEMENU;
}