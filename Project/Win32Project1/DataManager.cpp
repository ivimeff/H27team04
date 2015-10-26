#include "DataManager.h"


DataManager::DataManager(Renderer* _Renderer) : m_Renderer(_Renderer)
{

}

DataManager::~DataManager()
{
}

bool DataManager::load()
{
	loadTexture();
	return true;
}

void DataManager::loadTexture()
{
	//�V�[��
	m_Renderer->loadTexture(&title, "image/title.png");
	m_Renderer->loadTexture(&over, "image/over.png");
	m_Renderer->loadTexture(&tuto, "image/tuto.png");
	m_Renderer->loadTexture(&menu, "image/menu.png");

	//�L�����N�^�[
	m_Renderer->loadTexture(&anim, "image/anim.png");

	//�e�X�g�p
	m_Renderer->loadTexture(&green, "image/green.png");
	m_Renderer->loadTexture(&blue, "image/blue.png");
	m_Renderer->loadTexture(&yellow, "image/yellow.png");

	//�}�b�v�`�b�v
	m_Renderer->loadTexture(&floor, "image/floor.png");
	m_Renderer->loadTexture(&wall, "image/wall.png");

	//����
	m_Renderer->loadTexture(&select, "image/Selection.png");
	m_Renderer->loadTexture(&enter, "image/enter.png");
	m_Renderer->loadTexture(&space, "image/space.png");
	m_Renderer->loadTexture(&menu_tuto, "image/menu_tuto.png");
	m_Renderer->loadTexture(&menu_play, "image/menu_play.png");
	m_Renderer->loadTexture(&cursor, "image/cursor.png");

	//�M�~�b�N
	m_Renderer->loadTexture(&ironball, "image/ironball.png");
	m_Renderer->loadTexture(&suraimu, "image/sura.png");
}