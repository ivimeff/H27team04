#include "GamePad.h"
#include <DxLib.h>
//#include <assert.h>

using namespace State;

GamePad::GamePad() {}

GamePad::~GamePad() {}

void GamePad::init()
{
	beforeState = 0;
}

void GamePad::update()
{
	beforeState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

InputState GamePad::getInputButton(int button)
{
//#ifdef _DEBUG
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool now = (button & pad) != 0,
//#else
//	int pad = GetJoypadInputState(DX_INPUT_PAD1);
//	bool now = (button & pad) != 0,
//#endif
		before = (button & beforeState) != 0;

	//if ((pad & (PAD_INPUT_DOWN | PAD_INPUT_RIGHT | PAD_INPUT_10)) == PAD_INPUT_RIGHT + PAD_INPUT_DOWN + PAD_INPUT_10)
	//	MessageBox(GetMainWindowHandle(), "左上", "Check", MB_OK);

	return now > before ? STATE_DOWN :				// now = true, before = falseなら押した直後
		now < before ? STATE_UP :				// now = false, before = trueなら離した直後
		now & before ? STATE_PRESS : STATE_RELEASE;	// now とbeforeが同じでかつどちらもtrueなら押したまま、falseなら押されていない
}