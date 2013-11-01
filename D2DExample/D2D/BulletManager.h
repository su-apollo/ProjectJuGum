#pragma once
#include "Bullet.h"
#include "PlayScene.h"

#define MAX_BULLET_NUM 100

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	void ShotBullet(CMaincharacter * Player);
	void UpdateBullet(float dTime);
	void CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	void SetBulletLifeTime(CMainMap * Map, CBullet * Bullet);

	CBullet ** GetBulletArray() { return m_pBulletArray; }
	int GetBulletIndex() { return m_BulletIndex; }
	void AddBulletIndex() { ++m_BulletIndex; if(m_BulletIndex > MAX_BULLET_NUM){m_BulletIndex = 0;}}


private:
	static CBulletManager * m_pInstance;

	CBullet *	m_pBulletArray[MAX_BULLET_NUM];
	int			m_BulletIndex;

};

