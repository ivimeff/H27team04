#ifndef _GAMEPAD_
#define _GAMEPAD_

namespace State
{
	enum InputState
	{
		STATE_RELEASE	= 0,
		STATE_DOWN	= 1,
		STATE_PRESS	= 2,
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