#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "AccelBullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "Satellite.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0), m_AccelBulletIndex(0),
	m_SatelliteIndex(0)
{
}

CBulletManager::~CBulletManager(void)
{
}

//**************************************************************
//                         GetObj
//**************************************************************
CSatellite * CBulletManager::GetSatellite()
{
	++m_SatelliteIndex;
	m_SatelliteIndex %= MAX_SATELLITE_NUM;
	m_pSatelliteArray[m_SatelliteIndex]->SetVisible(true);

	return m_pSatelliteArray[m_SatelliteIndex];
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

//**************************************************************
//                         Skills
//**************************************************************
void CBulletManager::ShotSetupSatellite(NNObject* Player )
{
	CSatellite* pSatellite = GetSatellite();

	NNPoint point = Player->GetPosition();

	pSatellite->SetPosition(point);
}

void CBulletManager::ShotBullet(NNObject * Player)
{
	CBullet * pBullet = GetBullet();

	NNPoint point = Player->GetPosition();

	point.SetY( Player->GetPositionY() - SHOT_POINT);
	pBullet->SetPosition( point );
}

void CBulletManager::ShotAccelBullet(NNObject * Player)
{
 	CAccelBullet * pAccelBullet = GetAccelBullet();
 
 	NNPoint point = Player->GetPosition();
 
 	point.SetY( Player->GetPositionY() - SHOT_POINT);
	pAccelBullet->SetAccelation(ACCELBULLET_ACCELERATION);
 	pAccelBullet->SetPosition( point );
}

void CBulletManager::ShotSectorMixBullets( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();

	for (int i=0; i<n; ++i)
	{
		if ( i%2 == 0 )
		{
			CAccelBullet * pBullet = GetAccelBullet();
			float radius_of_Bullet = pBullet->GetMainCircle()->GetRadius();
			point.SetY( Player->GetPositionY() - SHOT_POINT );
			pBullet->SetPosition( point );
			pBullet->SetAccelation(ACCELBULLET_ACCELERATION);
			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
		else
		{
			CBullet * pBullet = GetBullet();
			float radius_of_Bullet = pBullet->GetMainCircle()->GetRadius();
			point.SetY( Player->GetPositionY() - SHOT_POINT );
			pBullet->SetPosition( point );
			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
	}
}

void CBulletManager::ShotSectorNormalBullets( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();

	for (int i=0; i<n; ++i)
	{
		CBullet* pBullet = GetBullet();
		float radius_of_Bullet = pBullet->GetMainCircle()->GetRadius();
		point.SetY( Player->GetPositionY() - SHOT_POINT );
		pBullet->SetPosition( point );
		pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
	}
}

//**************************************************************
//                          Update
//**************************************************************
void CBulletManager::UpdateObj( float dTime )
{
	UpdateSatellite(dTime);
	UpdateBullet(dTime);
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

void CBulletManager::UpdateSatellite( float dTime )
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		m_pSatelliteArray[i]->Update(dTime);
	}
}

//**************************************************************
//                         HitCheck
//**************************************************************
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

//**************************************************************
//                         LifeTime
//**************************************************************
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
		Bullet->SetDirection();
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
		Bullet->SetDirection();
		Bullet->SetSpeed();
		Bullet->SetAccelation();
		Bullet->SetPosition(0.f, 0.f);
		Bullet->SetVisible(false);
	}
}

//**************************************************************
//							etc
//**************************************************************
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

