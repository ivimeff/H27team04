#pragma once

#include "def.h"
#include "Task.h"
#include "ISceneChanger.h"
#include "DataManager.h"
#include "GamePad.h"
#include"SoundManager.h"
class Scene : public Task
{
public:
	Scene(DataManager* _DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound);
	virtual ~Scene(){}
	virtual void Initialize() override{}
	virtual void Finalize() override;
	virtual void Update() override{}
	// Scene�h���N���X����Draw���\�b�h��������
	// �����drawBack, drawMain, drawUI���������邱�ƂŃ��C���[�������\
	virtual void Draw() override;
protected:
	DataManager* m_pDataManager;
	Renderer* m_Renderer;
	SoundManager* m_pSound;
	GamePad* m_GamePad;
	int mImageHandle;	//�摜�i�[�p�ϐ�
	ISceneChanger* m_SceneChanger;
	bool end;
	bool side;
	// ��ԉ��̃��C���[
	virtual void drawBack();
	// ���Ԃ̃��C���[
	virtual void drawMain();
	// ��ԏ�̃��C���[
	virtual void drawUI();
};