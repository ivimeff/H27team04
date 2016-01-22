#include "Renderer.h"
#include "MapData.h"
#include <DxLib.h>
#include <numeric>
#include <string>
#include <fstream>

Renderer::Renderer()
{
	layer.insert(std::make_pair(def::L_BACK, MakeScreen(window::width, window::height, FALSE)));
	layer.insert(std::make_pair(def::L_MAIN, MakeScreen(window::width, window::height, TRUE)));
	layer.insert(std::make_pair(def::L_UI, MakeScreen(window::width, window::height, TRUE)));
	for (int i = 0; i < mapLayer.size(); ++i)
	{
		mapLayer[i] = def::DRAWORDER(
			MakeScreen(
				window::width,
				Map::chipSize, TRUE),
			def::Vector2());
	}
}

Renderer::~Renderer()
{

}

void Renderer::load(const char* pictureList)
{
	readLine(pictureList);
}

void Renderer::loadTexture(TextureID* id, char* fileName)
{
	//*id = LoadGraph(fileName, 0);
}

void Renderer::setLayer(def::LAYER newLayer)
{
	SetDrawScreen(layer[newLayer]);
}

void Renderer::setMapLayer(int i)
{
	SetDrawScreen(mapLayer[i].id.val);
	mapDrawFlg[i] = true;
}

void Renderer::setMapPos(int i, def::Vector2 pos)
{
	mapDrawFlg[i] = true;
	mapLayer[i].d = pos;
}

void Renderer::clearMapLayer()
{
	for (int i = 0; i < mapLayer.size(); ++i)
	{
		SetDrawScreen(mapLayer[i].id.val);
		ClearDrawScreen();
		mapDrawFlg[i] = false;
	}
}

void Renderer::begin()
{
	drawOrders.fill(std::vector<def::DRAWORDER>());
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_BACK]);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_MAIN]);
	ClearDrawScreen();
	SetDrawScreen(layer[def::L_UI]);
	ClearDrawScreen();
	for (auto itr = mapDrawFlg.begin(), e = mapDrawFlg.end(); itr != e; ++itr)
	{
		(*itr) = false;
	}
}

void Renderer::end()
{
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, layer[def::L_BACK], TRUE);
	for (int i = 0; i < mapLayer.size(); ++i)
	{
		if (!mapDrawFlg[i]) continue;
		DrawGraph(mapLayer[i].d.pos.x, mapLayer[i].d.pos.y, mapLayer[i].id.val, TRUE);
		drawOrderStart(i);
	}
	DrawGraph(0, 0, layer[def::L_MAIN], TRUE);
	DrawGraph(0, 0, layer[def::L_UI], TRUE);
	ScreenFlip();
}

void Renderer::drawTexture(TextureID id, float x, float y)
{
	DrawGraphF(x, y, resourceList[id], TRUE);
}

void Renderer::drawTexture(TextureID id, def::BaseVector2 pos)
{
	drawTexture(id, pos.x, pos.y);
}

void Renderer::drawTextureRect(TextureID id, float dx, float dy, float sx, float sy, float sw, float sh)
{
	DrawRectGraphF(dx, dy, sx, sy, sw, sh, resourceList[id], TRUE, FALSE);
}

void Renderer::drawTextureRect(TextureID id, def::BaseVector2 dPos, def::Rect sRect)
{
	drawTextureRect(id, dPos.x, dPos.y, sRect.left, sRect.top, sRect.width(), sRect.height());
}

void Renderer::drawModiTexture(TextureID id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	DrawModiGraphF(x1, y1, x2, y2, x3, y3, x4, y4, resourceList[id], FALSE);
}

void Renderer::drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4)
{
	drawModiTexture(id, pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, pos4.x, pos4.y);
}

void Renderer::drawTextureEx(TextureID id, float x1, float y1, float x2, float y2)
{
	DrawExtendGraphF(x1, y1, x2, y2, resourceList[id], FALSE);
}

void Renderer::drawTextureEx(TextureID id, def::Vector2 pos1, def::Vector2 pos2)
{
	drawTextureEx(id, pos1.x, pos2.y, pos2.x, pos2.y);
}

void Renderer::drawTextureEx(TextureID id, def::BaseRect dstRect)
{
	drawTextureEx(id, dstRect.left, dstRect.top, dstRect.right, dstRect.bottom);
}

void Renderer::drawTextureRectEx(TextureID id, float dx1, float dy1, float dx2, float dy2, float sx, float sy, float sw, float sh)
{
	DrawRectExtendGraphF(dx1, dy1, dx2, dy2, sx, sy, sw, sh, resourceList[id], FALSE);
}

void Renderer::drawTextureRectEx(TextureID id, def::BaseRect dstRect, def::BaseRect srcRect)
{
	drawTextureRectEx(id, dstRect.left, dstRect.top, dstRect.right, dstRect.bottom, srcRect.left, srcRect.top, srcRect.right, srcRect.bottom);
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

void Renderer::addDrawOrder(def::DRAWORDER order, int layer)
{
	int l =
		layer < 0 ? 0 :
		layer > def::maxMapLayer ? def::maxMapLayer :
		layer;
	drawOrders[l].push_back(order);
}

void Renderer::drawOrderStart(int layer)
{
	for (def::DRAWORDER order : drawOrders[layer])
	{
		//if (order.srcRect == 0)
		//{
		//	drawTexture(order.id, order.d.pos);
		//	continue;
		//}
		//drawTextureRect(order.id, order.d.pos, order.srcRect);
		switch (order.pat)
		{
		case def::DR_RECT:
			drawTextureRect(order.id.str, order.d.pos, order.srcRect);
			break;
		case def::DR_EX:
			drawTextureEx(order.id.str, order.d.rect);
			break;
		case def::DR_EX_RECT:
			drawTextureRectEx(order.id.str, order.d.rect, order.srcRect);
			break;
		default:
			drawTexture(order.id.str, order.d.pos);
			break;
		}
	}
}

//////////////////////////////////////////
// 説明　データを分解する。
// 第1引数　1行分のCSVデータ
// 第2引数　データベクター
// 戻り値　データ数　ファイルを開けなかった場合は-1になる
//////////////////////////////////////////
int Renderer::csvParser(std::string sorce, std::vector<std::string> &data)
{
	char *pSorce;
	std::string buf;
	//ポインタ初期化
	pSorce = &sorce.at(0);
	while (*pSorce != NULL)
	{
		// '#'を含む行は飛ばす
		if (*pSorce == '#') return 1;
		if (*pSorce == ',' || *pSorce == '\n' || *pSorce == '\r')
		{
			// カレントディレクトリが指定されていなければ追記する
			std::string pass = data.size() % 2 == 0 ? buf :
				buf.find(currentDir) == 0 ? buf :
				currentDir + buf;
			data.push_back(pass); //バッファをベクターに入れる

			//*pSorceが改行コードだったら（行の一番後ろまで読み込んだら）分解ループ終了
			if (*pSorce == '\n' || *pSorce == '\r') break;

			buf = "";//バッファを空っぽに
		}
		else buf += *pSorce; //つなぎ合わせる
		pSorce++; //次の文字に移動
	}
	return 0;
}

int Renderer::readLine(std::string fileName)
{
	//std::ifstream ifs("Sound/soundList.csv");
	std::ifstream ifs(fileName);
	std::string buf;
	std::vector<std::string> data;
	if (!ifs)
		return -1; //ファイルオープンエラー
	int i = 0;
	while (getline(ifs, buf)) {
		buf += "\n";//改行コードが削除されているので、付け足す

		// '#'が含まれていたら次の行へ
		if (csvParser(buf, data) != 0) continue;

		resourceList.insert(std::pair<std::string, int>(
			data[i], LoadGraph(data[i + 1].c_str()))
			);
		i += 2;
	}

	return 0;
}