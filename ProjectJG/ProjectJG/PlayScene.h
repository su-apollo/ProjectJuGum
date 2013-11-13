#pragma once
#include "NNScene.h"

class NNLabel;
class CMainMap;
class CFirstModeCharacter;
class CMaincharacter;
class CAccelBullet;
class CCurveBullet;

class CPlayScene : public NNScene
{
public:
	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B);

private:
	CFirstModeCharacter * m_Player1;	
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

	CAccelBullet* m_testbullet;
};

