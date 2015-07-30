#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include "gs.h"

class DataManager
{
public:
	DataManager();
	~DataManager();
	
	bool load();
	void loadTexture();

	gsTexture title;
	gsTexture over;
	gsTexture red;
	gsTexture green;
	gsTexture blue;
	gsTexture yellow;
	gsTexture select;
	gsTexture suraimu;

private:

};

#endif
