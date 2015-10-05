#include "GameOver.h"
#include <DxLib.h>

GameOver::GameOver(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad) : Scene(_DataManager, _Renderer, _GamePad) {}

GameOver::~GameOver()
{

}

void GameOver::init()
{
	end = false;
	over_x = 0;
	over_y = 0;
}

void GameOver::update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}
}

void GameOver::draw()
{
	m_Renderer->drawTexture(m_pDataManager->over, over_x, over_y);
}

GAME_MODE GameOver::nextScene()
{
	return GAME_MODE_GAMETITLE;
}

GAME_MODE GameOver::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMETITLE;
}