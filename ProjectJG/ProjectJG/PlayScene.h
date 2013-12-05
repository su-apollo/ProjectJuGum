#pragma once
#include "NNScene.h"
#include "GameOption.h"

class CMainMap;
class NNSprite;
class NNLabel;
class CFrame;
class CMaincharacter;

// 게임 플레이 씬. 배치는 씬에서, 게임관련 업데이트는 맵에서 함.
class CPlayScene : public NNScene
{
public:

	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool NetworkSetMenu();
	void CountDown(float dTime);

	void EndGame();

	void CameraMove( CMaincharacter* Player, float dTime );

private:

	CMainMap*	m_MainMap;
	CFrame*		m_Frame;
	
	bool		m_netsetup;
	NNLabel*	m_MenuLabel[NET_MENU_LAST];
	unsigned int m_KeyOn;

	NNLabel* m_CountNumLabel_3;
	NNLabel* m_CountNumLabel_2;
	NNLabel* m_CountNumLabel_1;
	float m_CountNum;
	bool m_DoCount;
	
};

