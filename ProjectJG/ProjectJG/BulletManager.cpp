#include "NNConfig.h"

#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "Satellite.h"
#include "Asteroid.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0),
	m_SatelliteIndex(0), m_AsteroidIndex(0)
{
}

CBulletManager::~CBulletManager(void)
{
}

//**************************************************************
//                         GetObj
//**************************************************************

CBullet * CBulletManager::GetBullet( EBulletType bullet_type )
{
	++m_BulletIndex;
	m_BulletIndex %= MAX_BULLET_NUM;
	CBullet* new_bullet = m_pBulletArray[m_BulletIndex];
	new_bullet->SetVisible(true);

	switch (bullet_type)
	{
	case NORMAL_BULLET:
		new_bullet->SetSpeed(BULLET_SPEED);
		return new_bullet;
	case ACCEL_BULLET:
		new_bullet->SetSpeed(ACCELBULLET_SPEED);
		new_bullet->SetAccel(ACCELBULLET_ACCEL);
		return new_bullet;
	case CURVE_BULLET:
		new_bullet->SetSpeed(CURVEBULLET_SPEED);
		new_bullet->SetAngularAccel(CURVEBULLET_ANGULAR_ACCEL);
		return new_bullet;
	default:
		break;
	}
	return nullptr;
}

CSatellite * CBulletManager::GetSatellite()
{
	++m_SatelliteIndex;
	m_SatelliteIndex %= MAX_SATELLITE_NUM;
	m_pSatelliteArray[m_SatelliteIndex]->SetVisible(true);

	return m_pSatelliteArray[m_SatelliteIndex];
}

CAsteroid* CBulletManager::GetAsteroid()
{
	++m_AsteroidIndex;
	m_AsteroidIndex %= MAX_ASTEROID_NUM;
	m_pAsteroidArray[m_AsteroidIndex]->SetVisible(true);

	return m_pAsteroidArray[m_AsteroidIndex];
}

//**************************************************************
//                         Skills
//**************************************************************
void CBulletManager::ShotSetupSatellite(CGameMoveObj* Player)
{
	CSatellite* pSatellite = GetSatellite();

	NNPoint point = Player->GetPosition();

	pSatellite->SetPosition(point);
}

void CBulletManager::ShotBullet(CGameMoveObj * Player, EBulletType bullet_type)
{
	CBullet * pBullet = GetBullet(bullet_type);
	pBullet->SetDirection(Player->GetShotDirection());
	pBullet->SetPosition( Player->GetShotPoint());
}

void CBulletManager::ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree , int n)
{
	float direction = Player->GetShotDirection();

	for ( int i = 0; i < n; ++i )
	{
		CBullet* pBullet = GetBullet(bullet_type);
		pBullet->SetPosition( Player->GetShotPoint());
		pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
	}
}

void CBulletManager::ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree, int n )
{
	float direction = Player->GetShotDirection();

	for ( int i = 0; i < n; ++i )
	{
		if ( i%2 == 0 )
		{
			CBullet * pBullet = GetBullet(bullet_type_1);
			pBullet->SetPosition( Player->GetShotPoint());

			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
		else
		{
			CBullet * pBullet = GetBullet(bullet_type_2);
			pBullet->SetPosition( Player->GetShotPoint());

			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
	}
}

void CBulletManager::ShotTornadoBullets(CGameMoveObj* Player, int n )
{
	NNPoint point = Player->GetPosition();
	float direction = 270;
	for ( int i = 0; i < n; ++i )
	{
		direction += 360/n;
		CBullet* pBullet = GetBullet(CURVE_BULLET);

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
			ShotSectorBullets(m_pSatelliteArray[i], NORMAL_BULLET);
		}
	}
}


//**************************************************************
//                          Update
//**************************************************************
void CBulletManager::UpdateObj( float dTime , CMaincharacter* Enemy)
{
	UpdateSatellite(dTime, Enemy);
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
}

void CBulletManager::UpdateSatellite(float dTime , CMaincharacter* Enemy)
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->Update(dTime, m_pSatelliteArray[i], Enemy);
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
		if(m_pBulletArray[i]->IsVisible() && m_pBulletArray[i]->HitCheck_CircleToCircle(Player))
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
			DestroyObj(m_pSatelliteArray[i]);
		}
	}
}

void CBulletManager::CheckLifeTime(CMainMap * Map)
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (m_pBulletArray[i]->IsVisible())
		{
			CheckLifeTime(Map, m_pBulletArray[i]);
		}
	}
}

void CBulletManager::CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj)
{
	float leftline = Map->GetLeftLine() - Obj->GetHitRadius();
	float rightline = Map->GetRightLine() + Obj->GetHitRadius();
	float botline = Map->GetBotLine() + Obj->GetHitRadius();
	float topline = Map->GetTopLine() - Obj->GetHitRadius();

	if (Obj->GetPositionX() < leftline || Obj->GetPositionX() > rightline
		|| Obj->GetPositionY() > botline || Obj->GetPositionY() < topline)
	{
		DestroyObj(Obj);
	}
}

//**************************************************************
//							Destroy
//**************************************************************
void CBulletManager::DestroyObj( CGameMoveObj* Bullet )
{
	Bullet->SetVisible(false);
	Bullet->InitMember();
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

void CBulletManager::ShotAsteroid(CMainMap* Map)
{
}

