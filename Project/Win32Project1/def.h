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
		Vector2 operator + (const Vector2 obj)
		{
			return Vector2(x + obj.x, y + obj.y);
		}
		Vector2 operator - (const Vector2 obj)
		{
			return Vector2(x - obj.x, y - obj.y);
		}
		Vector2 operator * (const Vector2 obj)
		{
			return Vector2(x * obj.x, y * obj.y);
		}
		Vector2 operator * (const float f)
		{
			return Vector2(x * f, y * f);
		}
		Vector2 operator / (const Vector2 obj)
		{
			return Vector2(x / obj.x, y / obj.y);
		}
		Vector2 operator / (const float f)
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
#pragma endregion "演算子関連　長いから省略"

#pragma region static
		// 0ベクトルを返す
		static const Vector2 Zero()
		{
			return Vector2(0.0f, 0.0f);
		}

		// 右への単位ベクトルを返す
		static const Vector2 Right()
		{
			return Vector2(1.0f, 0.0f);
		}

		// 左への単位ベクトルを返す
		static const Vector2 Left()
		{
			return Vector2(-1.0f, 0.0f);
		}

		// 上への単位ベクトルを返す
		static const Vector2 Up()
		{
			return Vector2(0.0f, -1.0f);
		}

		// 下への単位ベクトルを返す
		static const Vector2 Down()
		{
			return Vector2(0.0f, 1.0f);
		}
#pragma endregion "単位ベクトル等"

#pragma region other
		// ベクトルの長さを返す
		float length()
		{
			return sqrtf(x * x + y * y);
		}

		// 単位ベクトルを返す
		Vector2 dir()
		{
			return Vector2(
				x == 0 ? 0 : x / length(),
				y == 0 ? 0 : y / length());
		}

		// ベクトルの角度をラジアン角で返す
		float angle()
		{
			return atan2f(x, -y);
		}

		// ベクトル間の距離を返す
		float distance(Vector2 obj)
		{
			return Vector2(x - obj.x, y - obj.y).length();
		}
#pragma endregion "ベクトルの長さ、距離等"

	};

	struct Rect
	{
		float left, top, right, bottom;

		Rect() : left(0), top(0), right(0), bottom(0){}

		Rect(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		Rect(Vector2 pos, Vector2 size) :
			Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y) {}

		float width() { return right - left; }

		float height() { return bottom - top; }

		bool isCol(Rect _target)
		{
			return
				left < _target.right &&
				right > _target.left &&
				top < _target.bottom &&
				bottom > _target.top;
		}

		bool operator == (int val) const
		{
			return
				left == val &&
				right == val &&
				top == val &&
				bottom == val;
		}
	};
}

#endif