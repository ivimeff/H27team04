#include "gs.h"
#include "SceneManager.h"
#include <stdio.h>

SceneManager *m_pSceneManager;

void GameInit()
{
	m_pSceneManager = new SceneManager();
}

void GameLoop()
{
	m_pSceneManager->update();
	m_pSceneManager->draw();
}

void GameTerm()
{
	delete m_pSceneManager;
}