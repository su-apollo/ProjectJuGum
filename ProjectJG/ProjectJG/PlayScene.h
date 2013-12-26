#pragma once
#include "NNScene.h"
#include "GameOption.h"

class CMainMap;
class NNSprite;
class NNLabel;
class CFrame;
class CMaincharacter;
class NNSound;

// 게임 플레이 씬. 배치는 씬에서, 게임관련 업데이트는 맵에서 함.
class CPlayScene : public NNScene
{
public:

	CPlayScene( ENetworkMode GameMode, char* serverIP );
	virtual ~CPlayScene(void);

	void Init();

	void Render();
	void Update( float dTime );

	void NetworkSetMenu( ENetworkMode GameMode, char* serverIP );

	void EndGame();

	void CameraMove( CMaincharacter* Player, float dTime );

	void GameResultScene( float dTime );

private:

	CMainMap*		m_MainMap;
	CFrame*			m_Frame;
	
	bool			m_netsetup;

	NNLabel*		m_ResultMenu[RESULT_MENU_NUM];
	int				m_ResultMenuCursor;

	NNSound*		m_BackgroundSound;

	NNSprite*		m_SpriteRaymuWin;
	NNSprite*		m_SpriteRaymuLose;
	NNSprite*		m_SpriteMarisaWin;
	NNSprite*		m_SpriteMarisaLose;

	NNSprite*		m_LeftDoor;
	NNSprite*		m_RightDoor;

	ENetworkMode	m_GameMode;

	float			m_TimeForResultAnimation;
};

