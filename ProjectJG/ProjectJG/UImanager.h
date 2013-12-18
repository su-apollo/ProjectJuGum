#pragma once
#include "NNLabel.h"
#include "NNSprite.h"

class CMaincharacter;

// UI 관리는 모두 UI manager가 한다.
// 모든 UI는 부모가 UImanager 이고 Update 및 Render 도 모두 UImanager에서 한다.
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible )			{ m_FPSLabel->SetVisible( visible ); }
	void SetPlayer1CostLabelVisible( bool visible )	{ m_Player1CostLabel->SetVisible( visible ); }
	void SetPlayer2CostLabelVisible( bool visible )	{ m_Player2CostLabel->SetVisible( visible ); }
	void SetPlayer1PortraitVisible( bool visible )	{ m_Player1Portrait->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_Player2Portrait->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNSprite*	m_Player1Portrait;
	NNSprite*	m_Player2Portrait;

	NNObject*	m_UIList[10];

	int			m_UINum;


	// FPS
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPSBuffer[20];

	// cost
	NNLabel*	m_Player1CostLabel;
	wchar_t		m_Player1CostBuffer[100];
	NNLabel*	m_Player2CostLabel;
	wchar_t		m_Player2CostBuffer[100];

	
	
};

