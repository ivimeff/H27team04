#ifndef _GAMEPAD_
#define _GAMEPAD_

namespace State
{
	enum InputState
	{
		// ������Ă��Ȃ�
		STATE_RELEASE	= 0,
		// ������n�߂�
		STATE_DOWN	= 1,
		// ������Ă���
		STATE_PRESS	= 2,
		// �����ꂽ
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