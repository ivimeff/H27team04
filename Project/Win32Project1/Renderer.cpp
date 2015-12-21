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

void Renderer::load(const char* soundList)
{
	readLine(soundList);
}

void Renderer::loadTexture(TextureID* id, char* fileName)
{
	*id = LoadGraph(fileName, 0);
}

void Renderer::setLayer(def::LAYER newLayer)
{
	SetDrawScreen(layer[newLayer]);
}

void Renderer::setMapLayer(int i)
{
	SetDrawScreen(mapLayer[i].id);
	mapDrawFlg[i] = true;
}

void Renderer::setMapPos(int i, def::Vector2 pos)
{
	mapDrawFlg[i] = true;
	mapLayer[i].pos = pos;
}

void Renderer::clearMapLayer()
{
	for (int i = 0; i < mapLayer.size(); ++i)
	{
		SetDrawScreen(mapLayer[i].id);
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
		drawTexture(mapLayer[i].id, mapLayer[i].pos);
		drawOrderStart(i);
	}
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
		if (order.srcRect == 0)
		{
			drawTexture(order.id, order.pos);
			continue;
		}
		drawTextureRect(order.id, order.pos, order.srcRect);
	}
}

//////////////////////////////////////////
// �����@�f�[�^�𕪉�����B
// ��1�����@1�s����CSV�f�[�^
// ��2�����@�f�[�^�x�N�^�[
// �߂�l�@�f�[�^���@�t�@�C�����J���Ȃ������ꍇ��-1�ɂȂ�
//////////////////////////////////////////
int Renderer::csvParser(std::string sorce, std::vector<std::string> &data)
{
	char *pSorce;
	std::string buf;
	//�|�C���^������
	pSorce = &sorce.at(0);
	while (*pSorce != NULL)
	{
		// '#'���܂ލs�͔�΂�
		if (*pSorce == '#') return 1;
		if (*pSorce == ',' || *pSorce == '\n' || *pSorce == '\r')
		{
			data.push_back(buf); //�o�b�t�@���x�N�^�[�ɓ����

			//*pSorce�����s�R�[�h��������i�s�̈�Ԍ��܂œǂݍ��񂾂�j�������[�v�I��
			if (*pSorce == '\n' || *pSorce == '\r') break;

			buf = "";//�o�b�t�@������ۂ�
		}
		else buf += *pSorce; //�Ȃ����킹��
		pSorce++; //���̕����Ɉړ�
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
		return -1; //�t�@�C���I�[�v���G���[

	while (getline(ifs, buf)) {
		buf += "\n";//���s�R�[�h���폜����Ă���̂ŁA�t������

		// '#'���܂܂�Ă����玟�̍s��
		if (csvParser(buf, data) != 0) continue;
		//for (int i = 0; i < data.size(); i++)
		//{
		//	//�ǂݍ��񂾃f�[�^����������
		//	//�T���v���Ȃ̂ŁA�\���̂�
		//	//cout << data[i] << endl;

		//}
		resourceList.insert(std::make_pair(
			data[0].c_str(), LoadSoundMem(data[1].c_str()))
			);
	}

	return 0;
}