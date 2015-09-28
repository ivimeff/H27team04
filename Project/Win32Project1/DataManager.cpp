#include "DataManager.h"


DataManager::DataManager()
{

}

DataManager::~DataManager()
{
	gsReleaseTexture(title);
	gsReleaseTexture(over);
	gsReleaseTexture(anim);
	gsReleaseTexture(green);
	gsReleaseTexture(blue);
	gsReleaseTexture(yellow); 
	gsReleaseTexture(select);
	gsReleaseTexture(floor);
	gsReleaseTexture(wall);
	gsReleaseTexture(tuto);
	gsReleaseTexture(menu);
}

bool DataManager::load()
{
	loadTexture();
	return true;
}

void DataManager::loadTexture()
{
	gsLoadTexture(&title, "image/title.png", 0);
	gsLoadTexture(&over, "image/over.png", 0);
	gsLoadTexture(&anim, "image/anim.png", 0);
	gsLoadTexture(&green, "image/green.png", 0);
	gsLoadTexture(&blue, "image/blue.png", 0);
	gsLoadTexture(&yellow, "image/yellow.png", 0);
	gsLoadTexture(&select, "image/Selection.png", 0);
	gsLoadTexture(&suraimu, "image/sura.png", 0);
	gsLoadTexture(&floor, "image/floor.png", 0);
	gsLoadTexture(&wall, "image/wall.png", 0);
	gsLoadTexture(&tuto, "image/tuto.png", 0);
	gsLoadTexture(&menu, "image/menu.png", 0);
}