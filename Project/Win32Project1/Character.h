#ifndef _CHARACTER_
#define _CHARACTER_

#include "GamePlayBundle.h"

namespace def
{
	enum CTag
	{
		C_NONE,
		C_PLAYER,
		C_ENEMY,
		C_PASS_UP,
		C_PASS_DOWN,
		C_PASS_LEFT,
		C_PASS_RIGHT,
	};
}

class ICharacterMediator;

// �ʒu�������ۃN���X
class Character
{
public:
	Character(GamePlayBundle* _GamePlayBundle, def::CTag = def::C_NONE);
	Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::CTag = def::C_NONE);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void hited(Character* _target);

	//��
	virtual void hitLeft(Character* _target);
	//�E
	virtual void hitRight(Character* _target);
	//��
	virtual void hitTop(Character* _target);
	//��
	virtual void hitBottom(Character* _target);

	//��������擾
	def::Rect getObjLeftRect();
	//�E������擾
	def::Rect getObjRightRect();
	//�㔻��擾
	def::Rect getObjTopRect();
	//������擾
	def::Rect getObjBottomRect();

	void setPosition(def::Vector2 _position);
	bool isDead();
	def::Rect getRect();
	def::CTag getTag();
	def::Vector2 getPos();
	def::Vector2 getDrawPos();
protected:
	def::Vector2 position;
	def::Vector2 size, halfSize;
	def::Vector2 spsize, sphalfSize;
	DataManager* dataManager;
	MapData *mapData;
	Camera *camera;
	Renderer *renderer;
	GamePad* gamePad;
	ICharacterMediator* mediator;
	bool deadFlg;
	def::CTag tag;
	virtual def::DRAWORDER getDrawOrder(TextureID id, def::Vector2 pos, def::Rect srcRect = def::Rect());
};

#endif