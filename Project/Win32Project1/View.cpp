#include "View.h"
#include <DxLib.h>
#include "Keyboard.h"

View::View(DataManager *_DataManager, GamePad *_gamepad)
{
	m_DataManager = _DataManager;
	m_gamepad = _gamepad;
}

View::~View()
{

}

void View::init()
{
	ViewSize = minViewSize;
	EnergieFlg = TRUE;
	Energie = 0;
}

void View::updata()
{
	if (EnergieFlg == TRUE)
	{
		//パッドのLボタン
		if (Key_Get(KEY_INPUT_R) != 0 || m_gamepad->getInputButton(PAD_INPUT_5)){
			Energie++;
			ViewSize += 4;
		}
		else{
			Energie--;
			ViewSize -= 4;
		}
		if (Energie < 0){ Energie = 0; }
		if (Energie > 320){ Energie = 320; EnergieFlg = FALSE; }
	}
	else{
		Energie--;
		ViewSize -= 4;
		if (Energie < 0){
			Energie = 0;
			EnergieFlg = TRUE;
		}
	}

	if (ViewSize < minViewSize){ ViewSize = minViewSize; }
	if (ViewSize > maxViewSize){ ViewSize = maxViewSize; }
}

void View::draw()
{
	//パッドのRボタン
	//if (Key_Get(KEY_INPUT_E) != 0 || m_gamepad->getInputButton(PAD_INPUT_6))
	//{
		SetUseZBufferFlag(TRUE);
		//DrawCircle(512, 512, 32, RGB(0, 0, 0), TRUE);
		DrawCircleToZBuffer(View_X, View_Y, ViewSize, TRUE, DX_ZWRITE_MASK);
		DrawBox(0, 0, window::width, window::height, RGB(0, 0, 0), TRUE);
	//}
}
void View::SetPosition(def::Vector2 _pos)
{
	View_X = _pos.x;
	View_Y = _pos.y;
}