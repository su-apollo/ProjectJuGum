#pragma once
#include "NNScene.h"
#include "GameOption.h"

class NNSprite;
class NNLabel;
class NNSound;

// 게임을 실행하면 처음에 보이는 씬.

class CMainMenuScene : public NNScene
{
public:
	CMainMenuScene(void);
	virtual ~CMainMenuScene(void);

	void Render();
	void Update( float dTime );

private:
	NNSprite* m_Logo;
	NNSprite* m_BackGround;
	NNLabel* m_MenuLabel[MENU_NUM];

	NNSound* m_BackgroundSound;

	unsigned int m_KeyOn;
};

