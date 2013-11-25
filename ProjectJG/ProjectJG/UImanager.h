#pragma once
#include "NNLabel.h"

class CMaincharacter;

class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible )			{ m_FPSLabel->SetVisible( visible ); }
	void SetPlayer1CostLabelVisible( bool visible )	{ m_Player1CostLabel->SetVisible( visible ); }
	void SetPlayer2CostLabelVisible( bool visible )	{ m_Player2CostLabel->SetVisible( visible ); }

	NNLabel* GetFPSLabel() { return m_FPSLabel; }
	NNLabel* GetPlayer1CostLabel() { return m_Player1CostLabel; }
	NNLabel* GetPlayer2CostLabel() { return m_Player2CostLabel; }
	
	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	

	NNObject*	m_UIList[10];



	// FPS
	float		m_SumTime;
	NNLabel*	m_FPSLabel;
	wchar_t		m_FPSBuffer[20];

	// cost
	NNLabel*	m_Player1CostLabel;
	wchar_t		m_Player1CostBuffer[100];
	NNLabel*	m_Player2CostLabel;
	wchar_t		m_Player2CostBuffer[100];

	
	
};

