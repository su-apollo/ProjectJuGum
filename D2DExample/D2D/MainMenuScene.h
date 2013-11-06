#pragma once
#include "NNScene.h"

class NNSprite;
class NNLabel;

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

