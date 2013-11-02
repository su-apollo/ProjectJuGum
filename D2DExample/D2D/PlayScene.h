#pragma once
#include "MainMap.h"
#include "MainMenuScene.h"
#include "FirstModeCharic.h"

class CFirstModeCharic;

class CPlayScene : public NNScene
{
public:
	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool CircleToCircleHitCheck(NNPoint Apoint, float Aradius, NNPoint Bpoint, float Bradius);

private:
	CFirstModeCharic * m_Player1;
	CMaincharacter * m_Player2;
	CMainMap *	m_Map;

	// FPS
	float		m_SumTime;
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPS[20];

	void SetPlayerMoveArea(CMaincharacter * Player);
};

