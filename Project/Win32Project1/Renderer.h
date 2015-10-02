#ifndef _RENDERER_
#define _RENDERER_

#include "def.h"
#include "DataManager.h"
#include "gs.h"

namespace
{
	// テクスチャのポインタを格納させる
	typedef gsTexture TextureID;
}

class Renderer
{
public:
	Renderer();
	~Renderer();
	void loadTexture(TextureID* id, char* fileName);
	void begin();
	void end();
	void drawTexture(TextureID id, int x, int y);
	void drawTexture(TextureID id, def::Vector2 pos);
	void drawTextureRect(TextureID id, int dx, int dy, int sx, int sy, int sw, int sh);
	void drawTextureRect(TextureID id, def::Vector2 dPos, def::Rect sRect);

};

#endif