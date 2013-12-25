#pragma once
#include "NNLabel.h"
#include "NNSprite.h"
#include "GameOption.h"

class CMaincharacter;
class NNSpriteAtlas;

// UI 관리는 모두 UI manager가 한다.
// 모든 UI는 부모가 UImanager 이고 Update 및 Render 도 모두 UImanager에서 한다.
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible );
	void SetPlayer1CostLabelVisible( bool visible );
	void SetPlayer2CostLabelVisible( bool visible );
	void SetPlayer1PortraitVisible( bool visible )	{ m_PlayerPortrait[RAYMU]->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_PlayerPortrait[MARISA]->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

	void SetAtlasChar(NNSpriteAtlas* atlas, char number);	// 흐흐흐 겨우 돌아가는 함수 하드코딩이랑 다를 게 뭐야 ㅜㅜ

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[10];	// NNSpriteAtlas* 배열은 따로 관리.

	int			m_UINum;


	// FPS
	NNSprite*		m_FPSSprite;
	NNSpriteAtlas*	m_FPSLabel[20];
	char			m_FPSBuffer[20];

	// cost
	NNSprite*		m_PlayerPortrait[CHAR_NUM];
	NNSpriteAtlas*	m_PlayerCostLabel[CHAR_NUM][100];
	char			m_PlayerCostBuffer[CHAR_NUM][100];
		
	// 장식
	NNSprite*	m_pattern;
	NNSprite*	m_time;
	NNSprite*	m_flower;
};

