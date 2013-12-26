#pragma once
#include "Frame.h"
#include "NNRect.h"
#include "GameOption.h"

class NNAnimation;
class NNSprite;
class CMaincharacter;
class CAccelBullet;
class CCurveBullet;
class CCamera;
class CItemBox;

class CMainMap : public CFrame
{
public:
	CMainMap(ENetworkMode GameMode);
	virtual ~CMainMap(void);

	void Init();

	void Render();
	void Update( float dTime, CFrame* frame );

	CMaincharacter* GetPlayer1() { return m_Player1; }
	CMaincharacter* GetPlayer2() { return m_Player2; }

	CCamera*	GetCamera() { return m_Camera; }

	void		SetGameMode(ENetworkMode mode) {m_GameMode = mode;}
	void		SetPlayerMoveArea(CMaincharacter * Player, CFrame* frame);

	EGameResult GetGameResult() const { return m_GameResult; }
	void		SetGameResult(EGameResult val) { m_GameResult = val; }

	void		SummonItemBox(float dTime);

private:
	NNAnimation*	m_BackGround;

	float			m_CostPerSecond;
	float			m_TimeToHitCheckWait;

	CMaincharacter* m_Player1;	
	CMaincharacter* m_Player2;

	CItemBox*		m_ItemBox;

	ENetworkMode	m_GameMode;

	CCamera*		m_Camera;

	EGameResult		m_GameResult;

	float			m_PlayTimeSum;
	float			m_TimeForSummonItemBox;
};

