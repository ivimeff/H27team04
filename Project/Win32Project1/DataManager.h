#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include "Renderer.h"

class DataManager
{
public:
	DataManager(Renderer *_Rendrer);
	~DataManager();

	bool load();
	void loadTexture();
public:
	//シーン
	TextureID title;
	TextureID over;
	TextureID tuto;
	TextureID menu;

	//プレイヤー
	TextureID anim;
	TextureID spiritual;

	//テスト用
	TextureID green;
	TextureID blue;
	TextureID yellow;
	TextureID title2;

	//マップチップ
	TextureID floor;
	TextureID wall;

	//小物
	TextureID enter;
	TextureID space;
	TextureID menu_tuto;
	TextureID menu_play;
	TextureID select;
	TextureID menu_cursor;
	TextureID push_b;

	//ギミック
	TextureID ironball;
	TextureID suraimu;
	TextureID arrow;
	TextureID spidernet;
	TextureID block;

	//ポーズメニュー
	TextureID pause;
	TextureID pauseback;
	TextureID back;
	TextureID titleback;
	TextureID gameend;
	TextureID pause_cursor;

private:
	Renderer *m_Renderer;
};

#endif
