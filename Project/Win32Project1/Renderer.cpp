#include "Renderer.h"
#include "gs.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::loadTexture(TextureID* id, char* fileName)
{
	gsLoadTexture(id, fileName, 0);
}

void Renderer::begin()
{

}

void Renderer::end()
{

}

void Renderer::drawTexture(TextureID id, int x, int y)
{
	gsDraw2D(id, x, y);
}

void Renderer::drawTexture(TextureID id, def::Vector2 pos)
{
	drawTexture(id, pos.x, pos.y);
}

void Renderer::drawTextureRect(TextureID id, int dx, int dy, int sx, int sy, int sw, int sh)
{
	gsDraw2DPart(id, dx, dy, sx, sy, sw, sh);
}

void Renderer::drawTextureRect(TextureID id, def::Vector2 dPos, def::Rect sRect)
{
	drawTextureRect(id, dPos.x, dPos.y, sRect.left, sRect.top, sRect.width(), sRect.height());
}