#pragma once
#include "NNRect.h"
#include "GameOption.h"

class NNSprite;
class CMaincharacter;
class CAccelBullet;
class CCurveBullet;
class CCamera;


class CMainMap : public NNObject
{
public:
	CMainMap(void);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime );
	inline float GetTopLine() { return -m_MainFrame->GetHeight()*0.5f; }
	inline float GetBotLine() { return m_MainFrame->GetHeight()*0.5f; }
	inline float GetRightLine() { return m_MainFrame->GetWidth()*0.5f; }
	inline float GetLeftLine() { return -m_MainFrame->GetWidth()*0.5f; }

	CMaincharacter* GetPlayer1() { return m_Player1; }
	CMaincharacter* GetPlayer2() { return m_Player2; }

	CCamera*	GetCamera() { return m_Camera; }

	NNRect *	GetMainFrame() { return m_MainFrame; }
	float		GetHeight() {return m_Height;}
	float		GetWidth() {return m_Width;}

	bool		IsGameEnd();

	void		SetGameMode(ENetworkMode mode) {m_GameMode = mode;}

private:
	NNRect *	m_MainFrame;
	float		m_Height;
	float		m_Width;
	NNSprite*	m_BackGround;

	int			m_CurrentFrame;

	CMaincharacter * m_Player1;	
	CMaincharacter * m_Player2;

	void SetPlayerMoveArea(CMaincharacter * Player);

	ENetworkMode m_GameMode;

	CCamera*	m_Camera;
};

