#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "AccelBullet.h"
#include "CurveBullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "Satellite.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0), m_AccelBulletIndex(0), m_CurveBulletIndex(0),
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

CCurveBullet* CBulletManager::GetCurveBullet()
{
	++m_CurveBulletIndex;
	m_CurveBulletIndex %= MAX_CURVEBULLET_NUM;
	m_pCurveBulletArray[m_CurveBulletIndex]->SetVisible(true);

	return m_pCurveBulletArray[m_CurveBulletIndex];
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

void CBulletManager::ShotCurveBullet( NNObject * Player )
{
	CCurveBullet* pBullet = GetCurveBullet();

	NNPoint point = Player->GetPosition();
	point.SetY( Player->GetPositionY() - SHOT_POINT );
	pBullet->SetPosition( point );

	pBullet->SetDirection();
}

void CBulletManager::ShotSectorNormalBullets( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();

	for ( int i = 0; i < n; ++i )
	{
		CBullet* pBullet = GetBullet();
		point.SetY( Player->GetPositionY() - SHOT_POINT );
		pBullet->SetPosition( point );

		pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
	}
}

void CBulletManager::ShotSectorMixBullets( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();

	for ( int i = 0; i < n; ++i )
	{
		if ( i%2 == 0 )
		{
			CAccelBullet * pBullet = GetAccelBullet();
			point.SetY( Player->GetPositionY() - SHOT_POINT );
			pBullet->SetPosition( point );

			pBullet->SetAccelation(ACCELBULLET_ACCELERATION);
			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
		else
		{
			CBullet * pBullet = GetBullet();
			point.SetY( Player->GetPositionY() - SHOT_POINT );
			pBullet->SetPosition( point );

			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
	}
}

void CBulletManager::ShotTornadoBullets( NNObject* Player, int n )
{
	NNPoint point = Player->GetPosition();
	float direction = 270;
	for ( int i = 0; i < n; ++i )
	{
		direction += 360/n;
		CCurveBullet* pBullet = GetCurveBullet();

		point.SetX( Player->GetPositionX() + NNDegreeToX(direction)*SHOT_POINT );
		point.SetY( Player->GetPositionY() + NNDegreeToY(direction)*SHOT_POINT );
		pBullet->SetPosition( point );

		pBullet->SetDirection( direction );
	}
}



void CBulletManager::ShotSLSectorNormalBullet()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			ShotSectorNormalBullets(m_pSatelliteArray[i]);
		}
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
		if (m_pBulletArray[i]->IsVisible())
		{
			m_pBulletArray[i]->Update(dTime);
		}
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		if (m_pAccelBulletArray[i]->IsVisible())
		{
			m_pAccelBulletArray[i]->Update(dTime);
		}
	}
	for (int i = 0; i < MAX_CURVEBULLET_NUM; ++i)
	{
		if (m_pCurveBulletArray[i]->IsVisible())
		{
			m_pCurveBulletArray[i]->Update(dTime);
		}
	}
}

void CBulletManager::UpdateSatellite( float dTime )
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->Update(dTime, m_pSatelliteArray[i]);
		}
	}
}

//**************************************************************
//                         HitCheck
//**************************************************************
bool CBulletManager::CharacterHitCheck(CMaincharacter * Player)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if(m_pBulletArray[i]->IsVisible() && m_pBulletArray[i]->CharacterHitCheck(Player))
		{
			return true;
		}
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		if(m_pBulletArray[i]->IsVisible() && m_pAccelBulletArray[i]->CharacterHitCheck(Player))
		{
			return true;
		}
	}
	for (int i = 0; i < MAX_CURVEBULLET_NUM; ++i)
	{
		if(m_pCurveBulletArray[i]->IsVisible() && m_pCurveBulletArray[i]->CharacterHitCheck(Player))
		{
			return true;
		}
	}

	return false;
}

//**************************************************************
//                         LifeTime
//**************************************************************

void CBulletManager::CheckSatelliteLifeTime()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			DestroySatellite(m_pSatelliteArray[i]);
		}
	}
}

void CBulletManager::CheckBulletLifeTime(CMainMap * Map)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (m_pBulletArray[i]->IsVisible())
		{
			BulletLifeTime(Map, m_pBulletArray[i]);
		}
	}
	for (int i = 0; i < MAX_ACCELBULLET_NUM; ++i)
	{
		if (m_pAccelBulletArray[i]->IsVisible())
		{
			AccelBulletLifeTime(Map, m_pAccelBulletArray[i]);
		}
	}
	for (int i = 0; i < MAX_CURVEBULLET_NUM; ++i)
	{
		if (m_pCurveBulletArray[i]->IsVisible())
		{
			CurveBulletLifeTime(Map, m_pCurveBulletArray[i]);
		}
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
		DestroyBullet(Bullet);
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
		DestroyAccelBullet(Bullet);
	}
}

void CBulletManager::CurveBulletLifeTime( CMainMap* Map, CCurveBullet* Bullet )
{
	float leftline = Map->GetLeftLine() - Bullet->GetMainCircle()->GetRadius();
	float rightline = Map->GetRightLine() + Bullet->GetMainCircle()->GetRadius();
	float botline = Map->GetBotLine() + Bullet->GetMainCircle()->GetRadius();
	float topline = Map->GetTopLine() - Bullet->GetMainCircle()->GetRadius();

	if (Bullet->GetPositionX() < leftline || Bullet->GetPositionX() > rightline
		|| Bullet->GetPositionY() > botline || Bullet->GetPositionY() < topline)
	{
		DestroyCurveBullet(Bullet);
	}
}


//**************************************************************
//							Destroy
//**************************************************************
void CBulletManager::DestroyBullet( CBullet* Bullet )
{
	Bullet->SetDirection();
	Bullet->SetVisible(false);
}

void CBulletManager::DestroyAccelBullet( CAccelBullet* Bullet )
{
	Bullet->SetDirection();
	Bullet->SetSpeed();
	Bullet->SetAccelation();
	Bullet->SetVisible(false);
}

void CBulletManager::DestroyCurveBullet( CCurveBullet* Bullet )
{
	Bullet->SetDirection();
	Bullet->SetSpeed();
	Bullet->SetAngularAcceleration();
	Bullet->SetVisible(false);
}

void CBulletManager::DestroySatellite( CSatellite* Satellite )
{
	Satellite->SetVisible(false);
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

