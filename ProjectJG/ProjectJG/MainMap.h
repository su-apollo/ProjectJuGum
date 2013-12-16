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


class CMainMap : public CFrame
{
public:
	CMainMap(ENetworkMode GameMode);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime, CFrame* frame );

	CMaincharacter* GetPlayer1() { return m_Player1; }
	CMaincharacter* GetPlayer2() { return m_Player2; }

	CCamera*	GetCamera() { return m_Camera; }

	bool		IsGameEnd(float dTime);

	void		SetGameMode(ENetworkMode mode) {m_GameMode = mode;}
	void		SetPlayerMoveArea(CMaincharacter * Player, CFrame* frame);

	EGameResult GetGameResult() const { return m_GameResult; }
	void		SetGameResult(EGameResult val) { m_GameResult = val; }

private:
	NNAnimation*	m_BackGround;

	float			m_CostPerSecond;
	float			m_TimeToHitCheckWait;

	CMaincharacter* m_Player1;	
	CMaincharacter* m_Player2;

	ENetworkMode	m_GameMode;

	CCamera*		m_Camera;

	EGameResult		m_GameResult;
};

