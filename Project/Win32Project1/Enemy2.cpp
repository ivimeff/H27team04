#include "Enemy2.h"
#include "Player.h"
#include<math.h>
Enemy2::Enemy2(GamePlayBundle* _GamePlayBundle) : Enemy2(_GamePlayBundle, def::Vector2(0, 0)) {}

Enemy2::Enemy2(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_ENEMY)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Enemy2::~Enemy2() {}

void Enemy2::init()
{
	speed = def::Vector2(1.0f, 1.0f);
	nomalspeed = 1;
}

void Enemy2::update()
{
	speed = (Player::getpos() - position);
	//speed.dir();
	x = fabsf(speed.x);
	y = fabsf(speed.y);
	moveUpdate();
}

void Enemy2::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	renderer->drawTexture(dataManager->suraimu, drawPos);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif

}

void Enemy2::move()
{
	if (x <= 200 && y <= 200)
	{
		moveValue.y += speed.dir().y;
		moveValue.x += speed.dir().x;
	}
	else
	{
		moveValue.x += nomalspeed;
	}
}

void Enemy2::hited(Character* _target)
{
	if ((typeid(_target) == typeid(Player))) return;
	hit = true;
}

//�ǂɓ���������
void Enemy2::onDent()
{
	hit = true;
	nomalspeed = -nomalspeed;
}

//��邱��
//�v���C���[��ǂ������Ă���p�^�[��������
//�_���[�W����
//�N���̑��Ɉ������������Ƃ��̃X�g�b�v����