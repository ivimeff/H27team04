#include "Camera.h"
#include "MapData.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::setPosition(def::Vector2 _playerPos)
{
	// プレイヤーの中心に来るように設定
	def::Vector2 midPos = _playerPos - def::Vector2(window::width / 2, window::height / 2);

	// マップ端に来た時にカメラが進まないように調整
	position = def::Vector2(
		midPos.x < 0 ? 0 : midPos.x > Map::widthSize - window::width ? Map::widthSize - window::height : midPos.x,
		midPos.y < 0 ? 0 : midPos.y > Map::heightSize - window::height ? Map::heightSize - window::height : midPos.y
		);
}

def::Vector2 Camera::getPosition()
{
	return position;
}