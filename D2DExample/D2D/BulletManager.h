#pragma once
#include "Bullet.h"
#define MAX_BULLET_NUM 100

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();



private:
	static CBulletManager * m_pInstance;

	CBullet *	m_pBulletArray[MAX_BULLET_NUM];
	int			m_BulletIndex;

};

