#pragma once
#include "NNScene.h"
#include "Bullet.h"
#include "Maincharacter.h"

class CPlayScene : public NNScene
{
public:
	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	NNCREATE_FUNC(CPlayScene);

private:
	CMaincharacter * m_Player;
	CBullet *	m_Bullet[5];
	int			m_BulletIndex;
};

