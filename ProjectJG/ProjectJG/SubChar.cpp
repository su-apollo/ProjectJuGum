#include "NNConfig.h"
#include "SubChar.h"
#include "NNAnimation.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "NNSprite.h"
#include "NNResourceManager.h"
#include "NNAudioSystem.h"

CSubChar::CSubChar(ESubCharType type_of_char)
{
	m_Shotsound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_SUBCHAR_SHOT, false );

	if ( type_of_char == YUKARI )
	{
		m_BackgroundEffect = NNSprite::Create(L"Sprite/BackgroundEffect1.png");
		m_FlyMotion = NNAnimation::Create( 4, 0.1f,	
			L"Sprite/SubCharR1.png",
			L"Sprite/SubCharR2.png",
			L"Sprite/SubCharR3.png",
			L"Sprite/SubCharR4.png");
	}
	else if ( type_of_char == ALICE )
	{
		m_BackgroundEffect = NNSprite::Create(L"Sprite/BackgroundEffect2.png");
		m_FlyMotion = NNAnimation::Create( 4, 0.1f,	
			L"Sprite/SubCharB1.png",
			L"Sprite/SubCharB2.png",
			L"Sprite/SubCharB3.png",
			L"Sprite/SubCharB4.png");
	}

	m_BackgroundEffect->SetScale(1.5f, 1.5f);
	m_FlyMotion->SetScale(1.5f, 1.5f);
	AddChild( m_BackgroundEffect );
	AddChild( m_FlyMotion );

	m_Type = type_of_char;
	m_State = NONE_STATE;
	m_ShotTimeSum = 0.f;
	m_FanAttackBulletTime = 0.f;
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
	//백그라운드 이펙트 회전
	SetLifeTime(dTime + GetLifeTime());
	m_BackgroundEffect->SetRotation(100.f*GetLifeTime());

	UpdateShotDirection(enemy);
	UpdateShotPoint(SHOT_POINT);

	m_FlyMotion->SetRotation(GetShotDirection() + 90.f);
	m_FlyMotion->Update(dTime);
}

void CSubChar::YukariFanAttack( float dTime )
{
	float degree = 120.f;
	int n = 18;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(RAYMU_NORMAL_BULLET, 20.f, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(RAYMU_NORMAL_BULLET)->SetRotation(direction);
		pBullet->SetDirection(direction);
	}
}

void CSubChar::YukariAccelAttack( float dTime )
{
	float degree = 15.f;
	int n = 5;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(RAYMU_ACCEL_BULLET, 0, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(RAYMU_ACCEL_BULLET)->SetRotation(direction);
		pBullet->SetDirection(direction);
	}
}

void CSubChar::YukariCurveAttack( float dTime )
{
	float degree = 60.f;
	float shot_degree = -30.f;
	int n = 3;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() + shot_degree - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(RAYMU_CURVE_BULLET, 0, GetShotDirection());
		UpdateShotPoint(CURVE_SHOT_POINT);
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(RAYMU_CURVE_BULLET)->SetRotation(direction);
		pBullet->SetDirection(direction);
	}
}

void CSubChar::AliceNormalAttack( float dTime )
{
	CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(MARISA_BIG_BULLET, 0, GetShotDirection());
	UpdateShotPoint(BIG_SHOT_POINT);
	pBullet->SetPosition(GetShotPoint());
	pBullet->SetDirection(GetShotDirection());

}

void CSubChar::AliceStarAttack( float dTime )
{
	float degree = 60.f;
	int n = 5;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(MARISA_NORMAL_BULLET, 30.f, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(MARISA_NORMAL_BULLET)->SetRotation(direction);
		pBullet->SetDirection(direction);
	}

	degree = 60.f;
	n = 6;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(MARISA_NORMAL_BULLET, 50.f, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(MARISA_NORMAL_BULLET)->SetRotation(direction);
		pBullet->SetDirection(direction);
	}
}

void CSubChar::AliceBoomerangAttack( float dTime )
{
	float degree = 120.f;
	int n = 7;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(MARISA_RETAR_BULLET, 0.f, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->GetTexture(MARISA_RETAR_BULLET)->SetRotation(direction + 90.f);
		pBullet->SetDirection(direction);
	}
}


