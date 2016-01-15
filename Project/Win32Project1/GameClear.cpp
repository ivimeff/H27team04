#include "GameClear.h"
#include "Keyboard.h"
#include <DxLib.h>

GameClear::GameClear(DataManager* _DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Changer, _Sound){}

void GameClear::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/clear.png");
	m_pSound->play("GameClear");
}

void GameClear::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_RETURN) != 0){	//�G���^�[�������ꂽ��
		m_pSound->stop("GameClear");
		m_SceneChanger->ChangeScene(eScene_Title);//�^�C�g���ɕύX
	}
	timer++;
}

void GameClear::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//�����\��
	DrawString(0, 0, "�Q�[���N���A��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Enter�L�[�������ƃ^�C�g����ʂɖ߂�܂��B", GetColor(255, 0, 0));
#endif

	if ((timer % 100) < 50)
	{
		m_Renderer->drawTexture(m_pDataManager->push_b, window::width - 900, 500);
	}
}