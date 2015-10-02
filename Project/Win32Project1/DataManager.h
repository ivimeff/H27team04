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
	TextureID title;
	TextureID over;
	TextureID anim;
	TextureID green;
	TextureID blue;
	TextureID yellow;
	TextureID select;
	TextureID suraimu;
	TextureID floor;
	TextureID wall;
	TextureID tuto;
	TextureID menu;

private:
	Renderer *m_Renderer;
};

#endif
