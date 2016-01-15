#ifndef _GAMEPAD_
#define _GAMEPAD_

namespace State
{
	enum InputState
	{
		// ‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
		STATE_RELEASE	= 0,
		// ‰Ÿ‚³‚êŽn‚ß‚½
		STATE_DOWN	= 1,
		// ‰Ÿ‚³‚ê‚Ä‚¢‚é
		STATE_PRESS	= 2,
		// —£‚³‚ê‚½
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