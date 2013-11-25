#pragma once
#include "NNScene.h"

class CMainMap;
class NNSprite;
class NNLabel;

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

private:

	CMainMap *	m_Map;


	// cost
	float		m_CostPerSecond;
	
	NNSprite*	m_BackGround;

	bool		m_netsetup;
	NNLabel*	m_MenuLabel[3];
	unsigned int m_KeyOn;
};

