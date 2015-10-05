#ifndef _RENDERER_
#define _RENDERER_

#include "def.h"

namespace
{
	// テクスチャのポインタを格納させる
	typedef int TextureID;
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
	void drawString(const char* str, int x, int y, int color = 0xffffffff);
	void drawString(const char* str, def::Vector2 pos, int color = 0xffffffff);
	void drawRect(int x, int y, int w, int h, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Vector2 pos, def::Vector2 size, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Rect rect, int color = 0xffffffff, int fillFlg = 0);

};

#endif