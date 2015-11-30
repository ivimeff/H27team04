#ifndef _RENDERER_
#define _RENDERER_

#include "def.h"
#include <map>
#include <array>
#include <vector>

namespace
{
	// テクスチャのポインタを格納させる
	typedef int TextureID;
}

namespace def
{
	enum LAYER
	{
		L_BACK,
		L_MAIN,
		L_UI,
	};
	const int maxMapLayer = 16;

	struct DRAWORDER
	{
		Vector2 pos;
		Rect srcRect;
		TextureID id;
		DRAWORDER() : id(0), pos(def::Vector2()), srcRect(Rect()) {}
		DRAWORDER(TextureID _id, Vector2 _pos, Rect _srcRect) :
			id(_id), pos(_pos), srcRect(_srcRect){}
		DRAWORDER(TextureID _id, Vector2 _pos) :
			DRAWORDER(_id, _pos, Rect()){}

		def::DRAWORDER& operator = (const DRAWORDER& _order)
		{
			pos = _order.pos;
			srcRect = _order.srcRect;
			id = _order.id;
			return *this;
		}
	};
}

class Renderer
{
public:
	Renderer();
	~Renderer();
	void loadTexture(TextureID* id, char* fileName);
	// ループ内の描画前に呼び出す(主に表画面のクリア)
	void begin();
	// ループ内の描画後に呼び出す(主に表画面への反映)
	void end();
	// 描画対象レイヤーを指定する
	void setLayer(def::LAYER newLayer);
	void setMapLayer(int i);
	void setMapPos(int i, def::Vector2 pos);
	void clearMapLayer();
	void drawTexture(TextureID id, float x, float y);
	void drawTexture(TextureID id, def::Vector2 pos);
	void drawTextureRect(TextureID id, float dx, float dy, float sx, float sy, float sw, float sh);
	void drawTextureRect(TextureID id, def::Vector2 dPos, def::Rect sRect);
	void drawTextureEx(TextureID id, float x1, float y1, float x2, float y2);
	void drawTextureEx(TextureID id, def::Vector2 pos1, def::Vector2 pos2);
	void drawModiTexture(TextureID id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4);
	void drawString(const char* str, float x, float y, int color = 0xffffffff);
	void drawString(const char* str, def::Vector2 pos, int color = 0xffffffff);
	void drawRect(int x, int y, int w, int h, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Vector2 pos, def::Vector2 size, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Rect rect, int color = 0xffffffff, int fillFlg = 0);
	void setDrawBright(int R, int G, int B);
	void addDrawOrder(def::DRAWORDER order, int layer);
private:
	// コピーコンストラクタ禁止
	// 宣言だけで定義はしない
	Renderer(const Renderer&);
	// 代入禁止
	// 宣言だけで定義はしない
	Renderer& operator = (const Renderer&);
	std::map<def::LAYER, TextureID> layer;
	std::array<def::DRAWORDER, def::maxMapLayer> mapLayer;
	std::array<bool, def::maxMapLayer> mapDrawFlg;
	std::array< std::vector<def::DRAWORDER>, def::maxMapLayer> drawOrders;
	void drawOrderStart(int layer);
};

#endif