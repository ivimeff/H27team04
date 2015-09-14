#ifndef _CAMERA_
#define _CAMERA_

#include "gs.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void setPosition(D3DXVECTOR2 _playerPos);
	D3DXVECTOR2 getPosition();
private:
	D3DXVECTOR2 position;
};

#endif