#ifndef _GAMEPAD_
#define _GAMEPAD_

namespace State
{
	enum InputState
	{
		// 押されていない
		STATE_RELEASE	= 0,
		// 押され始めた
		STATE_DOWN	= 1,
		// 押されている
		STATE_PRESS	= 2,
		// 離された
		STATE_UP		= 3,
	};
}

class GamePad
{
public:
	GamePad();
	virtual ~GamePad();
	void init();
	void update();
	State::InputState getInputButton(int button);
private:
	int beforeState;
};

#endif