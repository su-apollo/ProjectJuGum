#pragma once
#include "NNScene.h"

class NNSprite;
class NNLabel;
class NNSound;

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
	NNLabel* m_MenuLabel[3];

	NNSound* m_BackgroundSound;

	unsigned int m_KeyOn;
};

