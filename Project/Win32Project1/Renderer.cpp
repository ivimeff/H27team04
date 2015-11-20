#include "Renderer.h"
#include <DxLib.h>

Renderer::Renderer()
{
	layer.insert(std::make_pair(def::L_BACK, MakeScreen(window::width, window::height, FALSE)));
	layer.insert(std::make_pair(def::L_MAIN, MakeScreen(window::width, window::height, TRUE)));
	layer.insert(std::make_pair(def::L_UI, MakeScreen(window::width, window::height, TRUE)));
}

Renderer::~Renderer()
{

}

void Renderer::loadTexture(TextureID* id, char* fileName)
{
	*id = LoadGraph(fileName, 0);
}

void Renderer::setLayer(def::LAYER newLayer)
{
	SetDrawScreen(layer[newLayer]);
}

void Renderer::begin()
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_BACK]);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_MAIN]);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_UI]);
	ClearDrawScreen();
}

void Renderer::end()
{
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, layer[def::L_BACK], TRUE);
	DrawGraph(0, 0, layer[def::L_MAIN], TRUE);
	DrawGraph(0, 0, layer[def::L_UI], TRUE);
	ScreenFlip();
}

void Renderer::drawTexture(TextureID id, float x, float y)
{
	DrawGraphF(x, y, id, TRUE);
}

void Renderer::drawTexture(TextureID id, def::Vector2 pos)
{
	drawTexture(id, pos.x, pos.y);
}

void Renderer::drawTextureRect(TextureID id, float dx, float dy, float sx, float sy, float sw, float sh)
{
	DrawRectGraphF(dx, dy, sx, sy, sw, sh, id, TRUE, FALSE);
}

void Renderer::drawTextureRect(TextureID id, def::Vector2 dPos, def::Rect sRect)
{
	drawTextureRect(id, dPos.x, dPos.y, sRect.left, sRect.top, sRect.width(), sRect.height());
}

void Renderer::drawModiTexture(TextureID id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	DrawModiGraphF(x1, y1, x2, y2, x3, y3, x4, y4, id, FALSE);
}

void Renderer::drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4)
{
	drawModiTexture(id, pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, pos4.x, pos4.y);
}

void Renderer::drawTextureEx(TextureID id, float x1, float y1, float x2, float y2)
{
	DrawExtendGraphF(x1, y1, x2, y2, id, FALSE);
}

void Renderer::drawTextureEx(TextureID id, def::Vector2 pos1, def::Vector2 pos2)
{
	drawTextureEx(id, pos1.x, pos2.y, pos2.x, pos2.y);
}

void Renderer::drawString(const char* str, float x, float y, int color)
{
	DrawStringF(x, y, str, color);
}

void Renderer::drawString(const char* str, def::Vector2 pos, int color)
{
	drawString(str, pos.x, pos.y, color);
}

void Renderer::drawRect(int x1, int y1, int x2, int y2, int color, int fillFlg)
{
	DrawBox(x1, y1, x2, y2, color, fillFlg);
}

void Renderer::drawRect(def::Vector2 pos, def::Vector2 size, int color, int fillFlg)
{
	drawRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y, color, fillFlg);
}

void Renderer::drawRect(def::Rect rect, int color, int fillFlg)
{
	DrawBox(rect.left, rect.top, rect.right, rect.bottom, color, fillFlg);
}

void Renderer::setDrawBright(int R, int G, int B)
{
	SetDrawBright(R, G, B);
}