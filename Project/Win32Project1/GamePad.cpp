#include "GamePad.h"
#include <DxLib.h>

using namespace State;

GamePad::GamePad() {}

GamePad::~GamePad() {}

void GamePad::init()
{
	beforeState = 0;
}

void GamePad::update()
{
#ifdef _DEBUG
	beforeState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
#else
	beforeState = GetJoypadInputState(DX_INPUT_PAD1);
#endif
}

InputState GamePad::getInputButton(int button)
{
#ifdef _DEBUG
	bool now = (button & GetJoypadInputState(DX_INPUT_KEY_PAD1)) != 0,
#else
	bool now = (button & GetJoypadInputState(DX_INPUT_PAD1)) != 0,
#endif
		before = (button & beforeState) != 0;
	return now > before ? STATE_DOWN :				// now = true, before = false‚È‚ç‰Ÿ‚µ‚½’¼Œã
		now < before ? STATE_UP :				// now = false, before = true‚È‚ç—£‚µ‚½’¼Œã
		now & before ? STATE_PRESS : STATE_RELEASE;	// now ‚Æbefore‚ª“¯‚¶‚Å‚©‚Â‚Ç‚¿‚ç‚àtrue‚È‚ç‰Ÿ‚µ‚½‚Ü‚ÜAfalse‚È‚ç‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
}