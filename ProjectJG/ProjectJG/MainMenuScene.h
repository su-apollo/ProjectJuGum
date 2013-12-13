#pragma once
#include "NNScene.h"
#include "GameOption.h"

#define LABEL_HEIGHT 80.f
#define LABEL_FONT_SIZE 40.f

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

private:
	NNSprite* m_Logo;
	NNSprite* m_BackGround;
	NNSound* m_BackgroundSound;

	NNLabel* m_MenuLabel[MENU_NUM];
	unsigned int m_KeyOn;

	NNLabel* m_LoadingLabel;

	bool	m_bChangeScene;
	ENetworkMode m_GameMode;

	NNLabel* m_NetMenuLabel[NET_MENU_NUM];
	wchar_t m_NetMenuBuffer[NET_MENU_NUM][30];
	char	m_serverIP[20];
};

