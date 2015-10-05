#include "Camera.h"
#include "MapData.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::setPosition(def::Vector2 _playerPos)
{
	// �v���C���[�̒��S�ɗ���悤�ɐݒ�
	def::Vector2 midPos = _playerPos - def::Vector2(window::width / 2, window::height / 2);

	// �}�b�v�[�ɗ������ɃJ�������i�܂Ȃ��悤�ɒ���
	position = def::Vector2(
		midPos.x < 0 ? 0 : midPos.x > Map::widthSize - window::width / 2 ? Map::widthSize - window::width / 2 : midPos.x,
		midPos.y < 0 ? 0 : midPos.y > Map::heightSize - window::height / 2 ? Map::heightSize - window::height / 2 : midPos.y
		);
}

def::Vector2 Camera::getPosition()
{
	return position;
}