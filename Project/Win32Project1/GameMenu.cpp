#include "GameMenu.h"
#include "Keyboard.h"
#include <DxLib.h>

typedef enum{
	eMenu_play,
	eMenu_tuto,

	eMenu_Num,
}eMenu;

static int NowSelect = eMenu_play;

GameMenu::GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Changer, _Sound)
{
}

void GameMenu::Initialize()
{
	end = false;
	side = false;
	mImageHandle = LoadGraph("Image/menu.png");

}

void GameMenu::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN)	//チュートリアルとかのシーンの分岐に使うやつ
	{
		side = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_DOWN || Key_Get(KEY_INPUT_DOWN) == 1){
		m_pSound->play("Menu");
		NowSelect = (NowSelect + 1) % eMenu_Num;
	}
	if (m_GamePad->getInputButton(PAD_INPUT_UP) == State::STATE_DOWN || Key_Get(KEY_INPUT_UP) == 1){
		m_pSound->play("Menu");
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
	}
	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_RETURN) == 1){
		switch (NowSelect){
		case eMenu_play:
			m_pSound->play("Menu");
			m_pSound->stop("TitleBGM");
			m_SceneChanger->ChangeScene(eScene_GamePlay);
			break;
		case eMenu_tuto:
			m_pSound->play("Menu");
			//m_pSound->stop("TitleBGM");
			m_SceneChanger->ChangeScene(eScene_Tutorial);
			break;
		}
	}
}

void GameMenu::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "メニュー画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Enterキーで決定", GetColor(255, 0, 0));
	DrawString(0, 40, "それぞれの画面に移行します。", GetColor(255, 0, 0));
#endif

	switch (NowSelect){
	case eMenu_play:
		m_Renderer->drawTexture("Menu_cursor", 540, 250);
		break;
	case eMenu_tuto:
		m_Renderer->drawTexture("Menu_cursor", 540, 500);
		break;
	}

	m_Renderer->drawTexture("Menu_play", 640, 250);

	m_Renderer->drawTexture("Menu_tuto", 640, 500);
}