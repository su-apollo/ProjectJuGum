#pragma once
#include "NNScene.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"

#include "NNApplication.h"
#include "PlayScene.h"
#include "NNSprite.h"


enum MENU_LIST
{
	MENU_PLAY,
	MENU_TEST,
	MENU_QUIT,
	MENU_LAST,
};

class CMainMenuScene : public NNScene
{
public:
	CMainMenuScene(void);
	virtual ~CMainMenuScene(void);

	void Render();
	void Update( float dTime );

private:
	NNSprite* m_Logo;
	NNLabel* m_MenuLabel[3];

	unsigned int m_KeyOn;
};

