#ifndef _DEF_H
#define _DEF_H

#include <math.h>

enum GAME_MODE
{
	GAME_MODE_GAMETITLE,
	GAME_MODE_GAMEMENU,
	GAME_MODE_TUTORIAL,
	GAME_MODE_GAMEPLAY,
	GAME_MODE_GAMEOVER
};

namespace window
{
	const int width = 1280;
	const int height = 720;
}

namespace def
{
	struct Vector2
	{
		float x, y;

		Vector2() : x(0), y(0) {}

		Vector2(float _x, float _y) : x(_x), y(_y) {}

#pragma region operator
		Vector2 operator = (const Vector2 obj)
		{
			x = obj.x; y = obj.y;
			return *this;
		}
		const Vector2 operator + (const Vector2 obj)
		{
			return Vector2(x + obj.x, y + obj.y);
		}
		const Vector2 operator - (const Vector2 obj)
		{
			return Vector2(x - obj.x, y - obj.y);
		}
		const Vector2 operator * (const Vector2 obj)
		{
			return Vector2(x * obj.x, y * obj.y);
		}
		const Vector2 operator * (const float f)
		{
			return Vector2(x * f, y * f);
		}
		const Vector2 operator / (const Vector2 obj)
		{
			return Vector2(x / obj.x, y / obj.y);
		}
		const Vector2 operator / (const float f)
		{
			return Vector2(x / f, y / f);
		}
		Vector2 operator += (const Vector2 obj)
		{
			x += obj.x; y += obj.y;
			return *this;
		}
		Vector2 operator -= (const Vector2 obj)
		{
			x -= obj.x; y -= obj.y;
			return *this;
		}
		Vector2 operator *= (const Vector2 obj)
		{
			x *= obj.x; y *= obj.y;
			return *this;
		}
		Vector2 operator /= (const Vector2 obj)
		{
			x /= obj.x; y /= obj.y;
			return *this;
		}
		bool operator == (const Vector2 obj) const
		{
			return (x == obj.x && y == obj.y);
		}
		bool operator != (const Vector2 obj) const
		{
			return (x != obj.x || y != obj.y);
		}
#pragma endregion "���Z�q�֘A�@��������ȗ�"

#pragma region static
		// 0�x�N�g����Ԃ�
		static const Vector2 Zero()
		{
			return Vector2(0.0f, 0.0f);
		}

		// �E�ւ̒P�ʃx�N�g����Ԃ�
		static const Vector2 Right()
		{
			return Vector2(1.0f, 0.0f);
		}

		// ���ւ̒P�ʃx�N�g����Ԃ�
		static const Vector2 Left()
		{
			return Vector2(-1.0f, 0.0f);
		}

		// ��ւ̒P�ʃx�N�g����Ԃ�
		static const Vector2 Up()
		{
			return Vector2(0.0f, -1.0f);
		}

		// ���ւ̒P�ʃx�N�g����Ԃ�
		static const Vector2 Down()
		{
			return Vector2(0.0f, 1.0f);
		}
#pragma endregion "�P�ʃx�N�g����"

		// �x�N�g���̒�����Ԃ�
		float length()
		{
			return sqrtf(x * x + y * y);
		}

		// �P�ʃx�N�g����Ԃ�
		Vector2 dir()
		{
			return Vector2(
				x == 0 ? 0 : x / length(),
				y == 0 ? 0 : y / length());
		}

		// �x�N�g���̊p�x�����W�A���p�ŕԂ�
		float angle()
		{
			return atan2f(x, -y);
		}

		// �x�N�g���Ԃ̋�����Ԃ�
		float distance(Vector2 obj)
		{
			return Vector2(x - obj.x, y - obj.y).length();
		}

	};

	struct Rect
	{
		float left, top, right, bottom;

		Rect() : left(0), top(0), right(0), bottom(0){}

		Rect(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		float width() { return left - right; }

		float height() { return top - bottom; }

		bool isCol(Rect _target)
		{
			return
				left < _target.right &&
				right > _target.left &&
				top < _target.bottom &&
				bottom > _target.top;
		}
	};
}

#endif