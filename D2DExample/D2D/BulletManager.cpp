#include "BulletManager.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0), m_AccelBulletIndex(0)
{
}

CBulletManager::~CBulletManager(void)
{
}

CBullet * CBulletManager::GetBullet()
{
	++m_BulletIndex;
	m_BulletIndex %= MAX_BULLET_NUM;
	m_pBulletArray[m_BulletIndex]->SetVisible(true);

	return m_pBulletArray[m_BulletIndex];
}

CAccelBullet * CBulletManager::GetAccelBullet()
{
	++m_AccelBulletIndex;
	m_AccelBulletIndex %= MAX_ACCELBULLET_NUM;
	m_pAccelBulletArray[m_AccelBulletIndex]->SetVisible(true);

	return m_pAccelBulletArray[m_AccelBulletIndex];
}

void CBulletManager::ShotBullet(CMaincharacter * Player)
{
	CBullet * pBullet = GetBullet();

	NNPoint point = Player->GetPosition();

	float radius_of_Player = Player->GetMainCircle()->GetRadius();
	float radius_of_Bullet = pBullet->GetMainCircle()->GetRadius();

	point.SetY( Player->GetPositionY() - (radius_of_Bullet + radius_of_Player));
	pBullet->SetPosition( point );
}

void CBulletManager::ShotAccelBullet(CMaincharacter * Player)
{
 	CAccelBullet * pAccelBullet = GetAccelBullet();
 
 	NNPoint point = Player->GetPosition();
 
 	float radius_of_Player = Player->GetMainCircle()->GetRadius();
 	float radius_of_Bullet = pAccelBullet->GetMainCircle()->GetRadius();
 
 	point.SetY( Player->GetPositionY() - (radius_of_Bullet + radius_of_Player));
	pAccelBullet->SetAccelation(ACCELBULLET_ACCELERATION);
 	pAccelBullet->SetPosition( point );
}

void CBulletManager::UpdateBullet(float dTime)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		m_pBulletArray[i]->Update(dTime);
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		m_pAccelBulletArray[i]->Update(dTime);
	}
}

bool CBulletManager::CharacterHitCheck(CMaincharacter * Player)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if(m_pBulletArray[i]->CharacterHitCheck(Player))
		{
			return true;
		}
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		if(m_pAccelBulletArray[i]->CharacterHitCheck(Player))
		{
			return true;
		}
	}

	return false;
}

void CBulletManager::CheckBulletLifeTime(CMainMap * Map)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		BulletLifeTime(Map, m_pBulletArray[i]);
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		AccelBulletLifeTime(Map, m_pAccelBulletArray[i]);
	}
}

void CBulletManager::BulletLifeTime(CMainMap * Map, CBullet * Bullet)
{
	float leftline = Map->GetLeftLine() - Bullet->GetMainCircle()->GetRadius();
	float rightline = Map->GetRightLine() + Bullet->GetMainCircle()->GetRadius();
	float botline = Map->GetBotLine() + Bullet->GetMainCircle()->GetRadius();
	float topline = Map->GetTopLine() - Bullet->GetMainCircle()->GetRadius();

	if (Bullet->GetPositionX() < leftline || Bullet->GetPositionX() > rightline
		|| Bullet->GetPositionY() > botline || Bullet->GetPositionY() < topline)
	{
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
}

void CBulletManager::AccelBulletLifeTime(CMainMap * Map, CAccelBullet * Bullet)
{
	float leftline = Map->GetLeftLine() - Bullet->GetMainCircle()->GetRadius();
	float rightline = Map->GetRightLine() + Bullet->GetMainCircle()->GetRadius();
	float botline = Map->GetBotLine() + Bullet->GetMainCircle()->GetRadius();
	float topline = Map->GetTopLine() - Bullet->GetMainCircle()->GetRadius();

	if (Bullet->GetPositionX() < leftline || Bullet->GetPositionX() > rightline
		|| Bullet->GetPositionY() > botline || Bullet->GetPositionY() < topline)
	{
		Bullet->SetSpeed();
		Bullet->SetAccelation();
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
}

CBulletManager* CBulletManager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CBulletManager();
	}

	return m_pInstance;
}

void CBulletManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}