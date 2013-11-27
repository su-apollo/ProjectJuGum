#pragma once
#include "NNScene.h"

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

	bool CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B);

	bool NetworkSetMenu();

	void EndGame();

	void CameraMove( CMaincharacter* Player, float dTime );

private:

	NNSprite*	m_BackGround;

	CMainMap *	m_MainMap;
	CFrame*		m_Frame;

	float		m_CostPerSecond;
	
	bool		m_netsetup;
	NNLabel*	m_MenuLabel[NET_MENU_LAST];
	unsigned int m_KeyOn;
	
};

