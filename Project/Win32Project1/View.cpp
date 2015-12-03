#include "View.h"
#include <DxLib.h>
#include "Keyboard.h"

View::View(DataManager *_DataManager)
{
	m_DataManager = _DataManager;
}

View::~View()
{

}

void View::init()
{
	ViewSize = 96;
	EnergieFlg = TRUE;
	Energie = 0;
}

void View::updata()
{
	if (EnergieFlg == TRUE)
	{
		if (Key_Get(KEY_INPUT_R) != 0){
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

	if (ViewSize < 96){ ViewSize = 96; }
	if (ViewSize > 256){ ViewSize = 256; }
}

void View::draw()
{
	if (Key_Get(KEY_INPUT_E) != 0)
	{
		SetUseZBufferFlag(TRUE);
		//DrawCircle(512, 512, 32, RGB(0, 0, 0), TRUE);
		DrawCircleToZBuffer(256, 256, ViewSize, TRUE, DX_ZWRITE_MASK);
		DrawBox(0, 0, 1280, 720, RGB(0, 0, 0), TRUE);
	}
}