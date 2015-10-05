#ifndef _GMAEPLAY_H
#define _GAMEPLAY_H

#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "Camera.h"
#include "GamePlayBundle.h"
#include "Renderer.h"

class GamePlay : public Scene
{
public:
	GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad);
	~GamePlay();

	void init();
	void update();
	void draw();
	GAME_MODE nextScene();
	GAME_MODE sideScene();	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
private:
	MapData *m_pMapData;
	Camera *camera;
	CharacterManager* m_CharacterManager;
	GamePlayBundle* gamePlayBundle;
};

#endif