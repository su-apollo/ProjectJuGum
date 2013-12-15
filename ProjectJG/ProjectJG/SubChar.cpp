#include "NNConfig.h"
#include "SubChar.h"
#include "NNAnimation.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"

CSubChar::CSubChar(ESubCharType type_of_char)
{
	if ( type_of_char == YUKARI )
	{
		m_FlyMotion = NNAnimation::Create( 4, 0.2f,	
			L"Sprite/SubCharR1.png",
			L"Sprite/SubCharR2.png",
			L"Sprite/SubCharR3.png",
			L"Sprite/SubCharR4.png");
	}
	else if ( type_of_char == ALICE )
	{
		m_FlyMotion = NNAnimation::Create( 4, 0.2f,	
			L"Sprite/SubCharB1.png",
			L"Sprite/SubCharB2.png",
			L"Sprite/SubCharB3.png",
			L"Sprite/SubCharB4.png");
	}

	m_FlyMotion->SetScale(1.5f, 1.5f);
	AddChild( m_FlyMotion );

	m_Type = type_of_char;
	m_State = NONE_STATE;
	m_ShotTimeSum = 0.f;
}


CSubChar::~CSubChar(void)
{
}

void CSubChar::Render()
{
	NNObject::Render();
}

void CSubChar::Update( float dTime, CMaincharacter* enemy )
{
	UpdateShotDirection(enemy);
	UpdateShotPoint();

	switch (m_Type)
	{
	case YUKARI:
		YukariNormalAttack(dTime);
		break;
	case ALICE:
		AliceNormalAttack(dTime);
		break;
	default:
		break;
	}

	m_FlyMotion->SetRotation(GetShotDirection() + 90.f);
	m_FlyMotion->Update(dTime);
}

void CSubChar::YukariNormalAttack( float dTime )
{
	m_ShotTimeSum += dTime;
	if (m_ShotTimeSum >= 2.f)
	{
		float degree = 30.f;
		int n = 3;

		for (int i = 0; i < n; ++i)
		{
			float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

			CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(RAYMU_ACCEL_BULLET, 0, GetShotDirection());
			pBullet->SetPosition(GetShotPoint());
			pBullet->SetDirection(direction);
		}
		m_ShotTimeSum = 0.f;
	}
}

void CSubChar::AliceNormalAttack( float dTime )
{
	m_ShotTimeSum += dTime;
	if (m_ShotTimeSum >= 3.f)
	{
		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(MARISA_BIG_BULLET, 0, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->SetDirection(GetShotDirection());

		m_ShotTimeSum = 0.f;
	}
}
