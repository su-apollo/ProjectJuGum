#pragma once

#include "NNSprite.h"
#include "NNSpriteAtlas.h"
#include "GameOption.h"

class CMaincharacter;
class NNSpriteAtlas;
class NNLabel;

// UI 관리는 모두 UI manager가 한다.
// 모든 UI는 부모가 UImanager 이고 Update 및 Render 도 모두 UImanager에서 한다.
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible ) { for(int i=0; i<20; ++i) m_FPSLabel[i]->SetVisible(visible); }
	void SetPlayer1CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[0][i]->SetVisible(visible); }
	void SetPlayer2CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[1][i]->SetVisible(visible); }
	void SetPlayer1PortraitVisible( bool visible )	{ m_PlayerPortrait[0]->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_PlayerPortrait[1]->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

	void Init();

	void SetAtlasChar(NNSpriteAtlas* atlas, char number);	// 흐흐흐 겨우 돌아가는 함수 하드코딩이랑 다를 게 뭐야 ㅜㅜ

	void SetTime(float dTime) { int minute = (int)(dTime/60); int second = (int)(dTime-minute); swprintf(m_TimeBuffer, 6, L"%02d:%02d", minute, second); }
	void RotateCharPortrait();

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[10];	// NNSpriteAtlas* 배열은 따로 관리.

	int			m_UINum;


	// FPS
	NNSprite*		m_FPSSprite;
	NNSpriteAtlas*	m_FPSLabel[UI_FPS_MAX_BUFFER_SIZE];
	char			m_FPSBuffer[UI_FPS_MAX_BUFFER_SIZE];

	// cost
	NNSprite*		m_PlayerPortrait[CHAR_NUM];
	NNSpriteAtlas*	m_PlayerCostLabel[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE];
	char			m_PlayerCostBuffer[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE];
		
	// 장식
	NNSprite*	m_pattern;
	NNSprite*	m_time;
	wchar_t		m_TimeBuffer[6];
	NNLabel*	m_TimeLabel;
	NNSprite*	m_flower;
};

