#pragma once
#include "NNRect.h"

class NNSprite;
class CMaincharacter;
class CAccelBullet;
class CCurveBullet;


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

	NNRect *	GetMainFrame() { return m_MainFrame; }
	float		GetHeight() {return m_Height;}
	float		GetWidth() {return m_Width;}

	bool		IsGameEnd();

private:
	NNRect *	m_MainFrame;
	float		m_Height;
	float		m_Width;
	NNSprite*	m_BackGround;

	int			m_CurrentFrame;

	CMaincharacter * m_Player1;	
	CMaincharacter * m_Player2;

	void SetPlayerMoveArea(CMaincharacter * Player);

	CAccelBullet* m_testbullet;
};

