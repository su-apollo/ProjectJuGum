#include "NNConfig.h"

#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "Satellite.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0),
	m_SatelliteIndex(0)
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
}

CSatellite * CBulletManager::GetSatellite()
{
	++m_SatelliteIndex;
	m_SatelliteIndex %= MAX_SATELLITE_NUM;
	m_pSatelliteArray[m_SatelliteIndex]->SetVisible(true);

	return m_pSatelliteArray[m_SatelliteIndex];
}

//**************************************************************
//                         Skills
//**************************************************************
void CBulletManager::ShotSetupSatellite(NNObject* Player)
{
	CSatellite* pSatellite = GetSatellite();

	NNPoint point = Player->GetPosition();

	pSatellite->SetPosition(point);
}

void CBulletManager::ShotBullet(NNObject * Player, EBulletType bullet_type)
{
	CBullet * pBullet = GetBullet(bullet_type);

	NNPoint point = Player->GetPosition();

	point.SetY( Player->GetPositionY() - SHOT_POINT);
	pBullet->SetPosition( point );
}

void CBulletManager::ShotTBullet( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();
	
	for ( int i = 0; i < n; ++i )
	{
		CBullet* pBullet = GetBullet(NORMAL_BULLET);
		point.SetY( Player->GetPositionY() - SHOT_POINT );
		pBullet->SetPosition( point );

		pBullet->SetDirection( direction + (degree * (i-1)));
	}
}

void CBulletManager::ShotSectorNormalBullets( NNObject* Player, float direction, float degree, int n )
{
	NNPoint point = Player->GetPosition();

	for ( int i = 0; i < n; ++i )
	{
		CBullet* pBullet = GetBullet(NORMAL_BULLET);
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
			CBullet * pBullet = GetBullet(ACCEL_BULLET);
			point.SetY( Player->GetPositionY() - SHOT_POINT );
			pBullet->SetPosition( point );

			pBullet->SetDirection( direction - degree/2 + degree/(n-1)*i );
		}
		else
		{
			CBullet * pBullet = GetBullet(NORMAL_BULLET);
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
	// agebreak : 앞에 헤더파일에서 지적한 것과 같은 문제
	// 총알의 종류가 계속 추가 되면 모든 코드들에 이렇게 계속 종류를 추가할 것인가? 
	// 이럴때 사용하라고  C++에서 다형성에 대해서 배우지 않았던가??
	// BattleShip에서 Ship들의 상속 구조에 대해서 생각해 볼 수 있도록...
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
}

void CBulletManager::BulletLifeTime(CMainMap * Map, CBullet * Bullet)
{
	float leftline = Map->GetLeftLine() - Bullet->GetHitRadius();
	float rightline = Map->GetRightLine() + Bullet->GetHitRadius();
	float botline = Map->GetBotLine() + Bullet->GetHitRadius();
	float topline = Map->GetTopLine() - Bullet->GetHitRadius();

	if (Bullet->GetPositionX() < leftline || Bullet->GetPositionX() > rightline
		|| Bullet->GetPositionY() > botline || Bullet->GetPositionY() < topline)
	{
		DestroyBullet(Bullet);
	}
}

//**************************************************************
//							Destroy
//**************************************************************
void CBulletManager::DestroyBullet( CBullet* Bullet )
{
	Bullet->SetVisible(false);
	Bullet->InitMember();
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

