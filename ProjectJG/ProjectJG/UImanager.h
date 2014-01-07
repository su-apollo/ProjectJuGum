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

#ifdef _DEBUG
	void SetFPSLabelVisible( bool visible ) { for(int i=0; i<20; ++i) m_FPSLabel[i]->SetVisible(visible); }
#endif

	NNSprite* GetRaymuSubChar() { return m_SubCharPortrait[RAYMU]; }
	NNSprite* GetMarisaSubChar() { return m_SubCharPortrait[MARISA]; }

	void SetPlayer1CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[0][i]->SetVisible(visible); }
	void SetPlayer2CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[1][i]->SetVisible(visible); }
	void SetPlayer1PortraitVisible( bool visible )	{ m_PlayerPortrait[0]->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_PlayerPortrait[1]->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

	void SetAtlasChar(NNSpriteAtlas* atlas, char number);	// 흐흐흐 겨우 돌아가는 함수 하드코딩이랑 다를 게 뭐야 ㅜㅜ

#ifdef _DEBUG
	void SetTime(float dTime) { int minute = (int)(dTime/60); int second = (int)(dTime-minute); swprintf(m_TimeBuffer, 6, L"%02d:%02d", minute, second); }
#endif
	
	void SetMyCharType( ECharcterType CharType );

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[50];	// NNSpriteAtlas* 배열은 따로 관리.

	int			m_UINum;

	// char 별로 다른 것들
	NNSprite*		m_PlayerPortrait[CHAR_NUM];
	NNSprite*		m_SubCharPortrait[CHAR_NUM];
	NNSprite*		m_SkillKeySprite[CHAR_NUM];


#ifdef _DEBUG
	// FPS
	NNSprite*		m_FPSSprite;
	NNSpriteAtlas*	m_FPSLabel[UI_FPS_MAX_BUFFER_SIZE];
	char			m_FPSBuffer[UI_FPS_MAX_BUFFER_SIZE];
#endif	

	// cost
	NNSpriteAtlas*	m_PlayerCostLabel[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE];
	char			m_PlayerCostBuffer[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE+1];
		
	// 장식
	NNSprite*	m_pattern;

#ifdef _DEBUG
	NNSprite*	m_time;
	wchar_t		m_TimeBuffer[6];
	NNLabel*	m_TimeLabel;
#else
	NNSprite*	m_SPLabel;
#endif

	NNSprite*	m_flower;
};

