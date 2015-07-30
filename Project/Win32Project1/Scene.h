#ifndef _SCENE_H_
#define _SCENE_H_

#include "def.h"
#include "DataManager.h"

class Scene
{
public:
	Scene(DataManager*);
	virtual ~Scene();
	virtual void init();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual GAME_MODE nextScene() = 0;
	bool isEnd();
protected:
	DataManager* m_pDataManager;
	bool end;

};

#endif