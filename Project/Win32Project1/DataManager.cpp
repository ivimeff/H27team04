#include "DataManager.h"


DataManager::DataManager()
{

}

DataManager::~DataManager()
{
	gsReleaseTexture(title);
	gsReleaseTexture(over);
	gsReleaseTexture(red);
	gsReleaseTexture(green);
	gsReleaseTexture(blue);
	gsReleaseTexture(yellow); 
	gsReleaseTexture(select);
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
	gsLoadTexture(&red, "image/red.png", 0);
	gsLoadTexture(&green, "image/green.png", 0);
	gsLoadTexture(&blue, "image/blue.png", 0);
	gsLoadTexture(&yellow, "image/yellow.png", 0);
	gsLoadTexture(&select, "image/Selection.png", 0);
	gsLoadTexture(&suraimu, "image/sura.png", 0);
}