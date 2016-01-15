#ifndef _RENDERER_
#define _RENDERER_

#include "def.h"
#include <map>
#include <array>
#include <vector>

namespace
{
	// �e�N�X�`���̃|�C���^���i�[������
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

	// �`��p�^�[��
	enum DRAWPATURN
	{
		DR_NORMAL = 0,
		DR_RECT,
		DR_EX,
		DR_EX_RECT,
	};

	const int maxMapLayer = 16;

	// ���C���[�����p�̕`��\��
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

		// �e�N�X�`���̕`��͈�
		Rect srcRect;
		// �e�N�X�`���ԍ�
		//TextureID id;
		// �`��p�^�[��
		DRAWPATURN pat;

		// �f�t�H���g
		//DRAWORDER() : id(0), pos(0, 0), size(0, 0), srcRect(Rect()) {}
		DRAWORDER() : id(0), d(), srcRect(), pat(DR_NORMAL) {}
		// ������W�A�`��T�C�Y�A�`���`(drawTextureRextEx)
		DRAWORDER(TextureID _id, Vector2 _pos, Vector2 _size, Rect _srcRect) :
			id(_id), d(Rect(_pos, _size)), srcRect(_srcRect), pat(DR_EX_RECT) {}
		// ������W�A�`���`(DrawTextureRect)
		DRAWORDER(TextureID _id, Vector2 _pos, Rect _srcRect) :
			id(_id), d(_pos), srcRect(_srcRect), pat(DR_RECT) {}
		// ������W�A�`��T�C�Y(drawTextureEx)
		DRAWORDER(TextureID _id, Vector2 _pos, Vector2 _size) :
			id(_id), d(Rect(_pos, _size)), srcRect(Rect()), pat(DR_EX) {}
		// ������W�̂�(drawTexture)
		DRAWORDER(TextureID _id, Vector2 _pos) :
			id(_id), d(_pos), srcRect(), pat(DR_NORMAL) {}
		// �e�N�X�`���̃|�C���^(int)�Ŏw�肷��(drawTexture)
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
	// ���[�v���̕`��O�ɌĂяo��(��ɕ\��ʂ̃N���A)
	void begin();
	// ���[�v���̕`���ɌĂяo��(��ɕ\��ʂւ̔��f)
	void end();
	// �`��Ώۃ��C���[���w�肷��
	void setLayer(def::LAYER newLayer);
	void setMapLayer(int i);
	void setMapPos(int i, def::Vector2 pos);
	void clearMapLayer();
	// �e�N�X�`���̕`�� ������W���w��
	void drawTexture(TextureID id, float x, float y);
	void drawTexture(TextureID id, def::BaseVector2 pos);
	// �e�N�X�`���̎w���`�����̕`��
	void drawTextureRect(TextureID id, float dx, float dy, float sx, float sy, float sw, float sh);
	void drawTextureRect(TextureID id, def::BaseVector2 dPos, def::Rect sRect);
	// �e�N�X�`���̊g��`��
	void drawTextureEx(TextureID id, float x1, float y1, float x2, float y2);
	void drawTextureEx(TextureID id, def::Vector2 pos1, def::Vector2 pos2);
	void drawTextureEx(TextureID id, def::BaseRect dstRect);
	// �e�N�X�`���̎w�蕔�����g��`��
	void drawTextureRectEx(TextureID id, float dx1, float dy1, float dx2, float dy2, float sx, float sy, float sw, float sh);
	void drawTextureRectEx(TextureID id, def::BaseRect dstRect, def::BaseRect srcRect);
	// �e�N�X�`���̎��R�ό`�`��
	void drawModiTexture(TextureID id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void drawModiTexture(TextureID id, def::Vector2 pos1, def::Vector2 pos2, def::Vector2 pos3, def::Vector2 pos4);
	// ������̕`��
	void drawString(const char* str, float x, float y, int color = 0xffffffff);
	void drawString(const char* str, def::Vector2 pos, int color = 0xffffffff);
	// �l�p�`�̕`��
	void drawRect(int x, int y, int w, int h, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Vector2 pos, def::Vector2 size, int color = 0xffffffff, int fillFlg = 0);
	void drawRect(def::Rect rect, int color = 0xffffffff, int fillFlg = 0);
	void setDrawBright(int R, int G, int B);
	void addDrawOrder(def::DRAWORDER order, int layer);
private:
	// �R�s�[�R���X�g���N�^�֎~
	// �錾�����Œ�`�͂��Ȃ�
	Renderer(const Renderer&);
	// ����֎~
	// �錾�����Œ�`�͂��Ȃ�
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