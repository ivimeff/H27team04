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
	m_Renderer->loadTexture(&title, "image/title.png");
	m_Renderer->loadTexture(&over, "image/over.png");
	m_Renderer->loadTexture(&anim, "image/anim.png");
	m_Renderer->loadTexture(&green, "image/green.png");
	m_Renderer->loadTexture(&blue, "image/blue.png");
	m_Renderer->loadTexture(&yellow, "image/yellow.png");
	m_Renderer->loadTexture(&select, "image/Selection.png");
	m_Renderer->loadTexture(&suraimu, "image/sura.png");
	m_Renderer->loadTexture(&floor, "image/floor.png");
	m_Renderer->loadTexture(&wall, "image/wall.png");
	m_Renderer->loadTexture(&tuto, "image/tuto.png");
	m_Renderer->loadTexture(&menu, "image/menu.png");
}