#include "NNConfig.h"
#include "NNSpriteAtlas.h"
#include "NNSprite.h"

#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "Asteroid.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0), m_AsteroidIndex(0)
#ifdef _DEBUG
	,m_TimeToCheckBulletNum(0.f), m_BulletNum(0)
#endif 	
{
}

CBulletManager::~CBulletManager(void)
{
}

//**************************************************************
//                         GetObj
//**************************************************************

//총알의 속성을 입력받은후 알맞은 속성으로 총알을 제작한다.
CBullet * CBulletManager::GetBullet( EBulletType bullet_type, float speed, float direction )
{
	++m_BulletIndex;
	m_BulletIndex %= MAX_BULLET_NUM;
	CBullet* new_bullet = m_pBulletArray[m_BulletIndex];
	new_bullet->SetVisible(true);

	switch (bullet_type)
	{
	case RAYMU_NORMAL_BULLET:
		new_bullet->SetBulletType(RAYMU_NORMAL_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(speed);
		new_bullet->GetTexture(RAYMU_NORMAL_BULLET)->SetRotation(direction);
		new_bullet->GetTexture(RAYMU_NORMAL_BULLET)->SetVisible(true);
		return new_bullet;

	case RAYMU_ACCEL_BULLET:
		new_bullet->SetBulletType(RAYMU_ACCEL_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(RAYMU_ACCEL_BULLET_SPEED);
		new_bullet->SetAccel(RAYMU_ACCEL_BULLET_ACCEL);
		new_bullet->GetTexture(RAYMU_ACCEL_BULLET)->SetRotation(direction);
		new_bullet->GetTexture(RAYMU_ACCEL_BULLET)->SetVisible(true);
		return new_bullet;

	case RAYMU_CURVE_BULLET:
		new_bullet->SetBulletType(RAYMU_CURVE_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(RAYMU_CURVE_BULLET_SPEED);
		new_bullet->SetAngularAccel(RAYMU_CURVE_BULLET_ANGULAR);
		new_bullet->GetTexture(RAYMU_CURVE_BULLET)->SetVisible(true);
		return new_bullet;

	case MARISA_NORMAL_BULLET:
		new_bullet->SetBulletType(MARISA_NORMAL_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(speed);
		new_bullet->GetTexture(MARISA_NORMAL_BULLET)->SetVisible(true);
		return new_bullet;

	case MARISA_BIG_BULLET:
		new_bullet->SetBulletType(MARISA_BIG_BULLET);
		new_bullet->SetHitRadius(BULLET_BIG_HIT_RADIUS);
		new_bullet->SetSpeed(MARISA_BIG_BULLET_SPEED);
		new_bullet->GetTexture(MARISA_BIG_BULLET)->SetVisible(true);
		return new_bullet;

	case MARISA_RETAR_BULLET:
		new_bullet->SetBulletType(MARISA_RETAR_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(MARISA_RETAR_BULLET_SPEED);
		new_bullet->SetSpeed(MARISA_RETAR_BULLET_ACCEL);
		new_bullet->GetTexture(MARISA_RETAR_BULLET)->SetVisible(true);
		return new_bullet;

	case FAIRY_NORMAL_BULLET:
		new_bullet->SetBulletType(FAIRY_NORMAL_BULLET);
		new_bullet->SetHitRadius(BULLET_HIT_RADIUS);
		new_bullet->SetSpeed(FAIRY_NORMAL_BULLET_SPEED);
		new_bullet->GetTexture(FAIRY_NORMAL_BULLET)->SetVisible(true);
		new_bullet->GetTexture(FAIRY_NORMAL_BULLET)->SetRotation(direction + 90.f);
		return new_bullet;
	default:
		break;
	}
	return nullptr;
}

CAsteroid* CBulletManager::GetAsteroid()
{
	++m_AsteroidIndex;
	m_AsteroidIndex %= MAX_ASTEROID_NUM;
	m_pAsteroidArray[m_AsteroidIndex]->SetVisible(true);

	m_pAsteroidArray[m_AsteroidIndex]->SetRandomSpeed();
	m_pAsteroidArray[m_AsteroidIndex]->SetDirection(135.f);

	return m_pAsteroidArray[m_AsteroidIndex];
}

//**************************************************************
//                         Skills
//**************************************************************

// void CBulletManager::ShotBullet(CGameMoveObj * Player, EBulletType bullet_type)
// {
// 	CBullet * pBullet = GetBullet(bullet_type, Player);
// 	pBullet->SetDirection(Player->GetShotDirection());
// 	pBullet->SetPosition( Player->GetShotPoint());
// }
// 
// void CBulletManager::ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree , int n)
// {
// 	float direction = Player->GetShotDirection();
// 
// 	for ( int i = 0; i < n; ++i )
// 	{
// 		CBullet* pBullet = GetBullet(bullet_type);
// 		pBullet->SetPosition( Player->GetShotPoint());
// 		pBullet->SetDirection( direction - degree*0.5f + degree/(n-1)*i );
// 	}
// }
// 
// void CBulletManager::ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree, int n )
// {
// 	float direction = Player->GetShotDirection();
// 
// 	for ( int i = 0; i < n; ++i )
// 	{
// 		CBullet * pBullet = ( i%2 == 0 ) ? GetBullet(bullet_type_1) : GetBullet(bullet_type_2);
// 		pBullet->SetPosition( Player->GetShotPoint());
// 		pBullet->SetDirection( direction - degree*0.5f + degree/(n-1)*i );
// 	}
// }
// 
// void CBulletManager::ShotTornadoBullets(CGameMoveObj* Player, int n )
// {
// 	NNPoint point = Player->GetPosition();
// 	float direction = 0.f;
// 
// 	for ( int i = 0; i < n; ++i )
// 	{
// 		direction += 360/n;
// 		CBullet* pBullet = GetBullet(CURVE_BULLET);
// 
// 		point.SetX( Player->GetPositionX() + NNDegreeToX(direction)*SHOT_POINT );
// 		point.SetY( Player->GetPositionY() + NNDegreeToY(direction)*SHOT_POINT );
// 		pBullet->SetPosition( point );
// 
// 		pBullet->SetDirection( direction );
// 	}
// }

//**************************************************************
//                          Update
//**************************************************************
void CBulletManager::UpdateObj(float dTime, CMaincharacter* Enemy, CMainMap* Map)
{
	UpdateAsteroid(dTime, Map);
	UpdateBullet(dTime, Map);
}

void CBulletManager::UpdateBullet(float dTime, CMainMap* Map)
{
	m_TimeToCheckBulletNum += dTime;

	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (m_pBulletArray[i]->IsVisible())
		{
#ifdef _DEBUG
			if (m_TimeToCheckBulletNum >= 5.0f)
				++m_BulletNum;
#endif
			m_pBulletArray[i]->Update(dTime);

			if(CheckLifeTime(Map, m_pBulletArray[i]))
				DestroyBullet(m_pBulletArray[i]);
		}
	}

	
	if (m_TimeToCheckBulletNum >= 5.0f)
	{
		printf_s("bullet num : %d\n", m_BulletNum);
		m_TimeToCheckBulletNum = 0.f;
		m_BulletNum = 0;
	}
}

void CBulletManager::UpdateAsteroid(float dTime, CMainMap* Map )
{
	for (int i = 0; i < MAX_ASTEROID_NUM; ++i)
	{
		if (m_pAsteroidArray[i]->IsVisible())
		{
			m_pAsteroidArray[i]->Update(dTime);
			if(CheckLifeTime(Map, m_pAsteroidArray[i]))
			{
				DestroyObj(m_pAsteroidArray[i]);
			}
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

bool CBulletManager::CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj)
{
	float leftline = Map->GetLeftLine() - Obj->GetHitRadius();
	float rightline = Map->GetRightLine() + Obj->GetHitRadius();
	float botline = Map->GetBotLine() + Obj->GetHitRadius();
	float topline = Map->GetTopLine() - Obj->GetHitRadius();

	if (Obj->GetPositionX() < leftline || Obj->GetPositionX() > rightline
		|| Obj->GetPositionY() > botline || Obj->GetPositionY() < topline)
	{
		return true;
	}
	return false;
}

//**************************************************************
//							Destroy
//**************************************************************
void CBulletManager::DestroyObj( CGameMoveObj* Obj )
{
	Obj->SetVisible(false);
	Obj->InitMember();
}

//총알을 파괴한다. 총알의 종류에 해당하는 텍스쳐를 안보이게 가린다.
void CBulletManager::DestroyBullet( CBullet* bullet )
{
	bullet->SetVisible(false);
	bullet->InitMember();
	bullet->GetTexture(bullet->GetBulletType())->SetVisible(false);
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
	CAsteroid* asteroid;
	int	temp;

	for (int i = 0; i < MAX_ASTEROID_NUM; ++i)
	{
		asteroid = GetAsteroid();

		if(rand()%2)
		{
			temp = rand() % (int)Map->GetHeight();
			asteroid->SetPosition(Map->GetLeftLine() + (float)temp, Map->GetTopLine());
		}
		else
		{
			temp = rand() % (int)Map->GetWidth();
			asteroid->SetPosition(Map->GetRightLine(), Map->GetTopLine() + (float)temp);
		}
	}
}

