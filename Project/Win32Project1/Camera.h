#ifndef _CAMERA_
#define _CAMERA_

#include "def.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void setPosition(def::Vector2 _playerPos);
	def::Vector2 getPosition();
private:
	def::Vector2 position;
	def::Vector2 cMax;
};

#endif