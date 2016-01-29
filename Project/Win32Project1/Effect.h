#pragma once

#include "Character.h"

namespace def
{
	struct AnimBase
	{
		// 時間経過
		int	time,
			// 描画時間
			maxTime,
			// アニメーションの横分割数
			width,
			// 合計アニメーション数
			size,
			// 現在のアニメーションページ
			page,
			// 1ページ表示する間隔
			pace;
		// 時間の指定さえすれば表示するアニメーション
		AnimBase(
			int _maxTime, int _size = 1, int _width = 1, int _pace = 1) :
			time(0), maxTime(_maxTime), size(_size),
			width(_width), page(0), pace(_pace) {}
		// 一周したら消えるアニメーション
		AnimBase(
			def::Vector2 _aSize, int _size, int _pace = 1) :
			AnimBase(_aSize.x * _aSize.y * _pace,
			_size, _aSize.x, _pace) {}
		bool update()
		{
			if (++time % pace == 0)
				if(++page >= size) page = 0;
			if (time >= maxTime) return true;
			return false;
		}
		Rect getAniRect(Vector2 eSize)
		{
			return Rect(
				page % width * eSize.x,
				page / width * eSize.y,
				(page % width + 1) * eSize.x,
				(page / width + 1) * eSize.y
				);
		}
	};
}

class Effect : public Character
{
public:
	Effect(char* _textureName, GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _size, def::AnimBase aBase);
	virtual ~Effect();
	void init();
	void update();
	void draw();
private:
	def::AnimBase aBase;
	char* textureName;
};