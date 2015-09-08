#include "Camera.h"
#include "MapData.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::setPosition(D3DXVECTOR2 _playerPos)
{
	position = _playerPos - D3DXVECTOR2(GS_WINDOW_WIDTH / 2, GS_WINDOW_HEIGHT / 2);

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x > Map::chipSize * Map::width) position.x = Map::chipSize * Map::width;
	if (position.y > Map::chipSize * Map::height) position.y = Map::chipSize * Map::height;
}

D3DXVECTOR2 Camera::getPosition()
{
	return position;
}