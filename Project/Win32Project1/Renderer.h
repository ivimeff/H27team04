#ifndef _RENDERER_
#define _RENDERER_

#include "def.h"
#include <map>
#include <array>
#include <vector>

namespace
{
	// テクスチャのポインタを格納させる
	typedef char* TextureID;
}

namespace def
{
	enum LAYER
	{
		L_BACK,
		L_MAIN,
		L_UI,
	};

	// 描画パターン
	enum DRAWPATURN
	{
		DR_NORMAL = 0,
		DR_RECT,
		DR_EX,
		DR_EX_RECT,
	};

	const int maxMapLayer = 16;

	// レイヤー分け用の描画予約
	struct DRAWORDER
	{
		union dst
		{
			BaseVector2 pos;
			BaseRect rect;
			dst() {}
			dst(BaseVector2 _pos) : pos(_pos) {}
			dst(BaseRect _rect) : rect(_rect) {}
		} d;

		union TextureIndex
		{
			char* str;
			int val;
			TextureIndex(char* _str) : str(_str) {}
			TextureIndex(int _val) : val(_val) {}
		} id;

		// テクスチャの描画範囲
		Rect srcRect;
		// テクスチャ番号
		//TextureID id;
		// 描画パターン
		DRAWPATURN pat;

		// デフォルト
		//DRAWORDER() : id(0), pos(0, 0), size(0, 0), srcRect(Rect()) {}
		DRAWORDER() : id(0), d(), srcRect(), pat(DR_NORMAL) {}
		// 左上座標、描画サイズ、描画矩形(drawTextureRextEx)
		DRAWORDER(TextureID _id, Vector2 _pos, Vector2 _size, Rect _srcRect) :
			id(_id), d(Rect(_pos, _size)), srcRect(_srcRect), pat(DR_EX_RECT) {}
		// 左上座標、描画矩形(DrawTextureRect)
		DRAWORDER(TextureID _id, Vector2 _pos, Rect _srcRect) :
			id(_id), d(_pos), srcRect(_srcRect), pat(DR_RECT) {}
		// 左上座標、描画サイズ(drawTextureEx)
		DRAWORDER(TextureID _id, Vector2 _pos, Vector2 _size) :
			id(_id), d(Rect(_pos, _size)), srcRect(Rect()), pat(DR_EX) {}
		// 左上座標のみ(drawTexture)
		DRAWORDER(TextureID _id, Vector2 _pos) :
			id(_id), d(_pos), srcRect(), pat(DR_NORMAL) {}
		// テクスチャのポインタ(int)で指定する(drawTexture)
		DRAWORDER(int _id, Vector2 _pos) :
			id(_id), d(_pos), srcRect(), pat(DR_NORMAL) {}

		def::DRAWORDER& operator = (const DRAWORDER& _order)
		{
			d = _order.d;
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
	void load(const char* pictureList);
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
	// テクスチャの描画 左上座標を指定
	void drawTexture(TextureID id, float x, float y);
	void drawTexture(TextureID id, def::BaseVector2 pos);
	// テクスチャの指定矩形部分の描画
	void drawTextureRect(TextureID id, float dx, float dy, float sx, float sy, float sw, float sh);
	void drawTextureRect(TextureID id, def::BaseVector2 dPos, def::Rect sRect);
	// テクスチャの拡大描画
	void drawTextureEx(TextureID id, float x1, float y1, float x2, float y2);
	void drawTextureEx(TextureID id, def::Vector2 pos1, def::Vector2 pos2);
	void drawTextureEx(TextureID id, def::BaseRect dstRect);
	// テクスチャの指定部分を拡大描画
	void drawTextureRectEx(TextureID id, float dx1, float dy1, float dx2, float dy2, float sx, float sy, float sw, float sh);
	void drawTextureRectEx(TextureID id, def::BaseRect dstRect, def::BaseRect srcRect);
	// テクスチャの自由変形描画
	void drawModiTexture(TextureID id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4);
	// 文字列の描画
	void drawString(const char* str, float x, float y, int color = 0xffffffff);
	void drawString(const char* str, def::Vector2 pos, int color = 0xffffffff);
	// 四角形の描画
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
	std::map<def::LAYER, int> layer;
	std::array<def::DRAWORDER, def::maxMapLayer> mapLayer;
	std::array<bool, def::maxMapLayer> mapDrawFlg;
	std::array< std::vector<def::DRAWORDER>, def::maxMapLayer> drawOrders;
	std::map<std::string, int> resourceList;
	void drawOrderStart(int layer);
	int csvParser(std::string sorce, std::vector<std::string> &data);
	int readLine(std::string fileName);
	const std::string currentDir = "Image/";
};

#endif