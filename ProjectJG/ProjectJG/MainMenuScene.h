#pragma once
#include "NNScene.h"
#include "GameOption.h"

class NNSprite;
class NNLabel;
class NNSound;

// ������ �����ϸ� ó���� ���̴� ��.

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
	NNLabel* m_LoadingLabel;

	NNSound* m_BackgroundSound;

	bool	m_bChangeScene;

	unsigned int m_KeyOn;
};
