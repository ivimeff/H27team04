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
	//�V�[��
	TextureID title;
	TextureID over;
	TextureID tuto;
	TextureID menu;

	//�v���C���[
	TextureID anim;

	//�e�X�g�p
	TextureID green;
	TextureID blue;
	TextureID yellow;
	
	//�}�b�v�`�b�v
	TextureID floor;
	TextureID wall;
	
	//����
	TextureID enter;
	TextureID space;
	TextureID menu_tuto;
	TextureID menu_play;
	TextureID select;
	TextureID cursor;

	//�M�~�b�N
	TextureID ironball;
	TextureID suraimu;

private:
	Renderer *m_Renderer;
};

#endif
