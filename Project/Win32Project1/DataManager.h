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
	TextureID tuto2;
	TextureID tuto3;
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
	TextureID treasure;
	TextureID door;

	//�M�~�b�N
	TextureID ironball;
	TextureID suraimu;
	TextureID arrow;
	TextureID spidernet;
	TextureID block;
	TextureID ironball_sp;
	TextureID arrow_sp;
	TextureID spidernet_sp;

	//�|�[�Y���j���[
	TextureID pause;
	TextureID pauseback;
	TextureID back;
	TextureID titleback;
	TextureID gameend;
	TextureID pause_cursor;

	//�v���C���[�f�[�^
	int Energie;
	int EnergieIcon;
	int Heart;

private:
	Renderer *m_Renderer;
};

#endif
