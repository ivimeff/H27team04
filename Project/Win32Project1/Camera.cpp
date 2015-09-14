#include "Camera.h"
#include "MapData.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::setPosition(D3DXVECTOR2 _playerPos)
{
	// プレイヤーの中心に来るように設定
	D3DXVECTOR2 midPos = _playerPos - D3DXVECTOR2(GS_WINDOW_WIDTH / 2, GS_WINDOW_HEIGHT / 2);

	// マップ端に来た時にカメラが進まないように調整
	position = D3DXVECTOR2(
		midPos.x < 0 ? 0 : midPos.x > Map::widthSize ? Map::widthSize : midPos.x,
		midPos.y < 0 ? 0 : midPos.y > Map::heightSize ? Map::heightSize : midPos.y
		);
}

D3DXVECTOR2 Camera::getPosition()
{
	return position;
}