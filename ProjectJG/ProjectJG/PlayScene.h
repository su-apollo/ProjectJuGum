#pragma once
#include "NNScene.h"

class CMainMap;
class NNSprite;
class NNLabel;

class CPlayScene : public NNScene
{
public:

	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B);

	bool NetworkSetMenu();

	void EndGame();

private:

	CMainMap *	m_Map;


	// FPS
	float		m_SumTime;
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPSBuffer[20];

	// cost
	float		m_CostPerSecond;
	NNLabel*	m_Player1CostLabel;
	wchar_t		m_Player1CostBuffer[100];
	NNLabel*	m_Player2CostLabel;
	wchar_t		m_Player2CostBuffer[100];

	NNSprite*	m_BackGround;

	bool		m_netsetup;
	NNLabel*	m_MenuLabel[3];
	unsigned int m_KeyOn;
};

