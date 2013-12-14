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

	bool		IsGameEnd();

	void		SetGameMode(ENetworkMode mode) {m_GameMode = mode;}

private:
	NNAnimation* m_BackGround;

	float		m_CostPerSecond;

	CMaincharacter * m_Player1;	
	CMaincharacter * m_Player2;

	void SetPlayerMoveArea(CMaincharacter * Player, CFrame* frame);

	ENetworkMode m_GameMode;

	CCamera*	m_Camera;
};

