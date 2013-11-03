#pragma once
#include "MainMap.h"
#include "MainMenuScene.h"
#include "FirstModeCharic.h"
#include <sstream>

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

	// cost
	float		m_CostPerSecond;
	NNLabel*	m_Player1CostLabel;
	wchar_t		m_Player1Cost[100];
	NNLabel*	m_Player2CostLabel;
	wchar_t		m_Player2Cost[100];

	void SetPlayerMoveArea(CMaincharacter * Player);
};

