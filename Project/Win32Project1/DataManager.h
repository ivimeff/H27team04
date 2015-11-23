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
	TextureID spiritual;

	//�e�X�g�p
	TextureID green;
	TextureID blue;
	TextureID yellow;
	TextureID title2;

	//�}�b�v�`�b�v
	TextureID floor;
	TextureID wall;

	//����
	TextureID enter;
	TextureID space;
	TextureID menu_tuto;
	TextureID menu_play;
	TextureID select;
	TextureID menu_cursor;
	TextureID push_b;

	//�M�~�b�N
	TextureID ironball;
	TextureID suraimu;
	TextureID arrow;
	TextureID spidernet;
	TextureID block;

	//�|�[�Y���j���[
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
