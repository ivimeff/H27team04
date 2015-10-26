#include "GameMenu.h"
#include "Keyboard.h"
#include <DxLib.h>

typedef enum{
	eMenu_play,
	eMenu_tuto,

	eMenu_Num,
}eMenu;

static int NowSelect = eMenu_play;

GameMenu::GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer) : Scene(_DataManager, _Renderer, _GamePad, _Changer)
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

	if (m_GamePad->getInputButton(PAD_INPUT_1) == State::STATE_DOWN)	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
	{
		side = true;
	}

	if (Key_Get(KEY_INPUT_DOWN) == 1){
		NowSelect = (NowSelect + 1) % eMenu_Num;
	}
	if (Key_Get(KEY_INPUT_UP) == 1){
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
	}
	if (Key_Get(KEY_INPUT_RETURN) == 1){
		switch (NowSelect){
		case eMenu_play:
			m_SceneChanger->ChangeScene(eScene_GamePlay);
			break;
		case eMenu_tuto:
			m_SceneChanger->ChangeScene(eScene_Tutorial);
			break;
		}
	}
}

void GameMenu::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//�����\��
	DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Enter�L�[�Ō���", GetColor(255, 0, 0));
	DrawString(0, 40, "���ꂼ��̉�ʂɈڍs���܂��B", GetColor(255, 0, 0));
#endif

	switch (NowSelect){
	case eMenu_play:
		m_Renderer->drawTexture(m_pDataManager->cursor, 550, 270);
		break;
	case eMenu_tuto:
		m_Renderer->drawTexture(m_pDataManager->cursor, 550, 520);
		break;
	}
	
	m_Renderer->drawTexture(m_pDataManager->menu_play, 640, 250);

	m_Renderer->drawTexture(m_pDataManager->menu_tuto, 640, 500);
}