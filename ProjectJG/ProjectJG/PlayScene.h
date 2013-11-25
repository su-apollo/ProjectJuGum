#pragma once
#include "NNScene.h"

class CMainMap;
class NNSprite;
class NNLabel;
class CFrame;
class CMaincharacter;

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

	CMainMap *	m_MainMap;


	// cost
	float		m_CostPerSecond;
	
	NNSprite*	m_BackGround;

	bool		m_netsetup;
	NNLabel*	m_MenuLabel[3];
	unsigned int m_KeyOn;

	CFrame*		m_Frame;
};

