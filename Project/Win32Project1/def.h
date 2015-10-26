#ifndef _DEF_H
#define _DEF_H

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

		bool operator < (const Vector2 obj) const
		{
			return (x < obj.x && y < obj.y);
		}

		bool operator >(const Vector2 obj) const
		{
			return (x > obj.x && y > obj.y);
		}
#pragma endregion "ââéZéqä÷òAÅ@í∑Ç¢Ç©ÇÁè»ó™"

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