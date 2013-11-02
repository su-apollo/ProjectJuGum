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
	
	void BulletShowerShot(CMaincharacter * Player);
	void ShotBullet(CMaincharacter * Player);
	void UpdateBullet(float dTime);
	void CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	
	//생산은 씬에서 해줘야함 불렛메니져는 생산된 불렛을 어레이로 보관하고 관리
	CBullet **	GetBulletArray() { return m_pBulletArray; }
	CBullet *	GetBullet();

private:
	static CBulletManager * m_pInstance;

	CBullet * m_pBulletArray[MAX_BULLET_NUM];
	int	m_BulletIndex;

	void SetBulletLifeTime(CMainMap * Map, CBullet * Bullet);
};

