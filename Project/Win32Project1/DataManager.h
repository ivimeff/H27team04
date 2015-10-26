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

	//テスト用
	TextureID green;
	TextureID blue;
	TextureID yellow;
	
	//マップチップ
	TextureID floor;
	TextureID wall;
	
	//小物
	TextureID enter;
	TextureID space;
	TextureID menu_tuto;
	TextureID menu_play;
	TextureID select;
	TextureID cursor;

	//ギミック
	TextureID ironball;
	TextureID suraimu;

private:
	Renderer *m_Renderer;
};

#endif
