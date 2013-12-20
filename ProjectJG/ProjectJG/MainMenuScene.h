#pragma once
#include "NNScene.h"
#include "GameOption.h"

class NNSprite;
class NNLabel;
class NNSound;

// 게임을 실행하면 처음에 보이는 씬.

class CMainMenuScene : public NNScene
{
public:
	CMainMenuScene(void);
	virtual ~CMainMenuScene(void);

	void Render();
	void Update( float dTime );

	void SetUpGameMode();
	void ChangeScene();
	void CancelModeSelection();

	void ShowCommand(int MenuIndex, wchar_t* command);
	void GetIPInput();
	void GetCurrentIP();

	void InitMenuLabel();
	void InitNetworkLabel();

private:
	// 배경
	NNSprite*		m_Loading;
	NNSprite*		m_BackGround;
	
	// 씬 전환시 넘길 parameter
	bool			m_bChangeScene;
	ENetworkMode	m_GameMode;
	char			m_serverIP[20];

	// 라벨들
	NNSprite*		m_InstructionLabel;
	NNSprite*		m_MenuLabel[MENU_NUM];
	NNSprite*		m_HighlightLabel[MENU_NUM];
	unsigned int	m_KeyOn;
	bool			m_bMenuSelected;

	NNLabel*		m_NetMenuLabel[NET_MENU_NUM];
	wchar_t			m_NetMenuBuffer[NET_MENU_NUM][30];

	NNSound*		m_BackgroundSound;
	NNSound*		m_OkSound;
	NNSound*		m_CancelSound;
	NNSound*		m_SelectSound;
	
};

