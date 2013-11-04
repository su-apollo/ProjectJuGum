#pragma once
#include "Bullet.h"
#include "AccelBullet.h"
#include "MainMenuScene.h"

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	void ShotAccelBullet(CMaincharacter * Player);
	void ShotBullet(CMaincharacter * Player);

	void UpdateBullet(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	
	//생산은 씬에서 해줘야함 불렛메니져는 생산된 불렛을 어레이로 보관하고 관리
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CAccelBullet ** GetAccelBulletArray() { return m_pAccelBulletArray; }
	

private:
	static CBulletManager * m_pInstance;

	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CAccelBullet *	m_pAccelBulletArray[MAX_ACCELBULLET_NUM];
	int				m_BulletIndex;
	int				m_AccelBulletIndex;

	void			SetBulletLifeTime(CMainMap * Map, NNObject * Bullet, float radius);
	CBullet *		GetBullet();
	CAccelBullet *	GetAccelBullet();
};

