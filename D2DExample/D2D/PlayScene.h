#pragma once
#include "NNScene.h"
#include "Bullet.h"
#include "Maincharacter.h"
#include "NNInputSystem.h"
#include "NNApplication.h"
#include "MainMap.h"

class CPlayScene : public NNScene
{
public:
	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool CircleToCircleHitCheck(NNPoint Apoint, float Aradius, NNPoint Bpoint, float Bradius);

private:
	CMaincharacter * m_Player1;
	CMaincharacter * m_Player2;
	CMainMap *	m_Map;
	
	// FPS
	float		m_SumTime;
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPS[20];

	void SetPlayerMoveArea(CMaincharacter * Player);
	void SetBolletLifeTime(CBullet * Bullet);
};

