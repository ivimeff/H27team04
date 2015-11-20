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
	// プレイヤーの中心に来るように設定
	def::Vector2 midPos = _playerPos - def::Vector2(window::width / 2, window::height / 2);

	// マップ端に来た時にカメラが進まないように調整
	position = def::Vector2(
		midPos.x < 0 ? 0 : midPos.x > cMax.x ? cMax.x : midPos.x,
		midPos.y < 0 ? 0 : midPos.y > cMax.y ? cMax.y : midPos.y
		);
}

def::Vector2 Camera::getPosition() const
{
	return position;
}