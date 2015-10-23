#include "Renderer.h"
#include <DxLib.h>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::loadTexture(TextureID* id, char* fileName)
{
	*id = LoadGraph(fileName, 0);
}

void Renderer::begin()
{
	ClearDrawScreen();
}

void Renderer::end()
{
	ScreenFlip();
}

void Renderer::drawTexture(TextureID id, int x, int y)
{
	DrawGraph(x, y, id, FALSE);
}

void Renderer::drawTexture(TextureID id, def::Vector2 pos)
{
	drawTexture(id, pos.x, pos.y);
}

void Renderer::drawTextureRect(TextureID id, int dx, int dy, int sx, int sy, int sw, int sh)
{
	DrawRectGraph(dx, dy, sx, sy, sw, sh, id, TRUE, FALSE);
}

void Renderer::drawTextureRect(TextureID id, def::Vector2 dPos, def::Rect sRect)
{
	drawTextureRect(id, dPos.x, dPos.y, sRect.left, sRect.top, sRect.width(), sRect.height());
}

void Renderer::drawString(const char* str, int x, int y, int color)
{
	DrawString(x, y, str, color);
}

void Renderer::drawString(const char* str, def::Vector2 pos, int color)
{
	drawString(str, pos.x, pos.y, color);
}

void Renderer::drawRect(int x1, int y1, int x2, int y2, int color, int fillFlg)
{
	DrawBox(x1, y1, x2, y2, color, fillFlg);
}

void Renderer::drawRect(def::Vector2 pos1, def::Vector2 pos2, int color, int fillFlg)
{
	drawRect(pos1.x, pos1.y, pos2.x, pos2.y, color, fillFlg);
}

void Renderer::drawRect(def::Rect rect, int color, int fillFlg)
{
	DrawBox(rect.left, rect.top, rect.right, rect.bottom, color, fillFlg);
}

void Renderer::drawModiTexture(TextureID id, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, id, FALSE);
}

void Renderer::drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4)
{
	drawModiTexture(id, pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, pos4.x, pos4.y);
}