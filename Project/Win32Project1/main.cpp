#include "DxLib.h"
#include "SceneManager.h"
#include "def.h"
#include "Keyboard.h"

class Fps{
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps(){
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update(){
		if (mCount == 0){ //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N){ //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw(){
		DrawFormatString(window::width - 80, 0, GetColor(255, 255, 255), "FPS:%.1f", mFps);
	}

	void Wait(){
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0){
			Sleep(waitTime);	//待機
		}
	}
};

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef _DEBUG
#else
	ChangeWindowMode(TRUE);		// ウィンドウモード
	SetWindowText("test");
#endif
	SetGraphMode(window::width, window::height, 16);		// 画面モードのセット

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Fps fps;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	Renderer* renderer = new Renderer();
	SceneManager* sceneManager = new SceneManager();

	sceneManager->init();
	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Update();
		Key_Update();
		sceneManager->update();
		renderer->begin();
		sceneManager->draw();
#ifdef _DEBUG
		fps.Draw();
#endif
		renderer->end();
		fps.Wait();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}