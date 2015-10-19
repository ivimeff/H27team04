#include "GameMenu.h"
#include <DxLib.h>

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

	if (m_GamePad->getInputButton(PAD_INPUT_1) == State::STATE_DOWN)	//チュートリアルとかのシーンの分岐に使うやつ
	{
		side = true;
	}

	if (CheckHitKey(KEY_INPUT_J) != 0){	//Jが押されたら
		m_SceneChanger->ChangeScene(eScene_GamePlay);//ゲーム画面に変更
	}

	if (CheckHitKey(KEY_INPUT_RETURN) != 0){	//スペースが押されたら
		m_SceneChanger->ChangeScene(eScene_Tutorial);//チュートリアルに変更
	}
}

void GameMenu::Draw()
{
	/*m_Renderer->drawTexture(m_pDataManager->menu, menu_x, menu_y);
	m_Renderer->drawTexture(m_pDataManager->green, menu_t_x, menu_t_y);
	m_Renderer->drawTexture(m_pDataManager->blue, menu_t_x, menu_p_y);*/

	Scene::Draw();
	//文字表示
	DrawString(0, 0, "メニュー画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Jキーを押すとゲーム画面に移行します。", GetColor(255, 0, 0));
	DrawString(0, 40, "Enterキーを押すとチュートリアル画面に移行します。", GetColor(255, 0, 0));
}