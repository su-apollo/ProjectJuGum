#include "BulletManager.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0)
{
}

CBulletManager::~CBulletManager(void)
{
}

void CBulletManager::ShotBullet(CMaincharacter * Player)
{
	NNPoint point = Player->GetPosition();
	float radius_of_Player = Player->GetMainCircle()->GetRadius();
	float radius_of_Bullet = m_pBulletArray[m_BulletIndex]->GetMainCircle()->GetRadius();
	point.SetY( Player->GetPositionY() - (radius_of_Bullet + radius_of_Player));
	m_pBulletArray[m_BulletIndex]->SetPosition( point );
	if (m_BulletIndex < ( MAX_BULLET_NUM - 1))
	{
		++m_BulletIndex;
	}
}

void CBulletManager::UpdateBullet(float dTime)
{
	for (int i = 0; i < m_BulletIndex; ++i)
	{
		m_pBulletArray[i]->Update(dTime);
	}
}

void CBulletManager::CharacterHitCheck(CMaincharacter * Player)
{
	for (int i = 0; i < m_BulletIndex; ++i)
	{
		if(m_pBulletArray[i]->CharacterHitCheck(Player))
		{
			NNSceneDirector::GetInstance()->ChangeScene(new CMainMenuScene);
		}
	}
}

void CBulletManager::CheckBulletLifeTime(CMainMap * Map)
{
	for (int i = 0; i < m_BulletIndex; ++i)
	{
		SetBulletLifeTime(Map, m_pBulletArray[i]);
	}
}

void CBulletManager::SetBulletLifeTime(CMainMap * Map, CBullet * Bullet)
{
	float leftline = Map->GetPositionX() + Map->GetMainFrame()->GetWidth()/2 + Bullet->GetMainCircle()->GetRadius();
	float rightline = Map->GetPositionX() - Map->GetMainFrame()->GetWidth()/2 - Bullet->GetMainCircle()->GetRadius();
	float botline = Map->GetPositionY() + Map->GetMainFrame()->GetHeight()/2 + Bullet->GetMainCircle()->GetRadius();
	float topline = Map->GetPositionY() - Map->GetMainFrame()->GetHeight()/2 - Bullet->GetMainCircle()->GetRadius();

	if (Bullet->GetPositionX() > leftline )
	{
		Bullet->SetPosition(0.f, 0.f);
		--m_BulletIndex;
	}
	else if (Bullet->GetPositionX() < rightline)
	{
		Bullet->SetPosition(0.f, 0.f);
		--m_BulletIndex;
	}
	else if (Bullet->GetPositionY() > botline)
	{
		Bullet->SetPosition(0.f, 0.f);
		--m_BulletIndex;
	}
	else if (Bullet->GetPositionY() < topline)
	{
		Bullet->SetPosition(0.f, 0.f);
		--m_BulletIndex;
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