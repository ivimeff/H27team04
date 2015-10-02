#include "DxLib.h"
#include "SceneManager.h"
#include "def.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef _DEBUG
#else
	ChangeWindowMode(TRUE);		// ウィンドウモード
	SetWindowText("test");
	SetGraphMode(window::width, window::height, 16);		// 画面モードのセット
#endif

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	Renderer* renderer = new Renderer();
	SceneManager* sceneManager = new SceneManager();

	sceneManager->init();
	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		sceneManager->update();
		renderer->begin();
		sceneManager->draw();
		renderer->end();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}