#include "Camera.h"
#include "MapData.h"
#include <math.h>

Camera::Camera()
{
	cMax = def::Vector2(std::max(0, Map::widthSize - window::width),
		std::max(0, Map::heightSize - window::height));
}

Camera::~Camera() {}

void Camera::setPosition(def::Vector2 _playerPos)
{
	// �v���C���[�̒��S�ɗ���悤�ɐݒ�
	def::Vector2 midPos = _playerPos - def::Vector2(window::width / 2, window::height / 2);

	// �}�b�v�[�ɗ������ɃJ�������i�܂Ȃ��悤�ɒ���
	position = def::Vector2(
		midPos.x < 0 ? 0 : midPos.x > cMax.x ? cMax.x : midPos.x,
		midPos.y < 0 ? 0 : midPos.y > cMax.y ? cMax.y : midPos.y
		);
}

def::Vector2 Camera::getPosition() const
{
	return position;
}