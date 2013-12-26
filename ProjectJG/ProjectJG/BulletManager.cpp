#include "NNConfig.h"
#include "NNSpriteAtlas.h"
#include "NNSprite.h"

#include "BulletManager.h"
#include "MainMap.h"
#include "Bullet.h"
#include "MainMenuScene.h"
#include "Maincharacter.h"
#include "ItemBox.h"

CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void) : m_BulletIndex(0), m_TimeToCheckBulletNum(0.f), m_BulletNum(0)
{
}

CBulletManager::~CBulletManager(void)
{
}

void CBulletManager::InitAllBullet()
{
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (m_pBulletArray[i]->IsVisible())
			DestroyBullet(m_pBulletArray[i]);
	}
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
		new_bullet->SetAccel(MARISA_RETAR_BULLET_ACCEL);
		new_bullet->GetTexture(MARISA_RETAR_BULLET)->SetVisible(true);
		new_bullet->GetTexture(MARISA_RETAR_BULLET)->SetRotation(direction + 90.f);
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

//**************************************************************
//                          Update
//**************************************************************
void CBulletManager::UpdateObj(float dTime, CMaincharacter* Enemy, CMainMap* Map)
{
	UpdateBullet(dTime, Map);
}

void CBulletManager::UpdateBullet(float dTime, CMainMap* Map)
{
	m_TimeToCheckBulletNum += dTime;

	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		if (m_pBulletArray[i]->IsVisible())
		{
			if (m_TimeToCheckBulletNum >= 5.0f)
				++m_BulletNum;
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

bool CBulletManager::CheckLifeTime(CMainMap* Map, CBullet* Obj)
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


