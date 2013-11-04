#include "BulletManager.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0)
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
	CAccelBullet * pBullet = GetAccelBullet();

	NNPoint point = Player->GetPosition();

	float radius_of_Player = Player->GetMainCircle()->GetRadius();
	float radius_of_Bullet = pBullet->GetMainCircle()->GetRadius();

	point.SetY( Player->GetPositionY() - (radius_of_Bullet + radius_of_Player));
	pBullet->SetPosition( point );
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
		SetBulletLifeTime(Map, m_pBulletArray[i], m_pBulletArray[i]->GetMainCircle()->GetRadius());
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		SetBulletLifeTime(Map, m_pAccelBulletArray[i], m_pAccelBulletArray[i]->GetMainCircle()->GetRadius());
	}
}

void CBulletManager::SetBulletLifeTime(CMainMap * Map, NNObject * Bullet, float radius)
{
	float leftline = Map->GetPositionX() + Map->GetMainFrame()->GetWidth()/2 +radius;
	float rightline = Map->GetPositionX() - Map->GetMainFrame()->GetWidth()/2 - radius;
	float botline = Map->GetPositionY() + Map->GetMainFrame()->GetHeight()/2 + radius;
	float topline = Map->GetPositionY() - Map->GetMainFrame()->GetHeight()/2 - radius;

	if (Bullet->GetPositionX() > leftline )
	{
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
	else if (Bullet->GetPositionX() < rightline)
	{
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
	else if (Bullet->GetPositionY() > botline)
	{
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
	else if (Bullet->GetPositionY() < topline)
	{
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