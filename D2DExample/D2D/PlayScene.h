#pragma once
#include "NNScene.h"
#include "Bullet.h"
#include "Maincharacter.h"
#include "NNInputSystem.h"
#include "NNApplication.h"
#include "MainMap.h"

#define MAX_BULLET_NUM 100

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
	CBullet *	m_Bullet1[MAX_BULLET_NUM];
	CBullet *	m_Bullet2[MAX_BULLET_NUM];
	int			m_BulletIndex1;
	int			m_BulletIndex2;

	// FPS
	float		m_SumTime;
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPS[20];

	void SetPlayerMoveArea(CMaincharacter * Player);
	void SetBolletLifeTime(CBullet * Bullet);
};

