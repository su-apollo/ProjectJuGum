#pragma once
#include "NNScene.h"
#include "Bullet.h"
#include "Player.h"

class CPlaytest : public NNScene
{
public:
	CPlaytest(void);
	virtual ~CPlaytest(void);

	void Render();
	void Update( float dTime );

	NNCREATE_FUNC(CPlaytest);

private:
	CPlayer *	m_Player;
	CBullet *	m_Bullet[5];
	int			m_BulletIndex;
};

