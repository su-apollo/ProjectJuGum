#include "NNConfig.h"

#include "Bullet.h"
#include "NNAnimation.h"
#include "Fairy.h"
#include "NNCircle.h"
#include "BulletManager.h"
#include "Maincharacter.h"
#include "NNSpriteAtlas.h"

CFairy::CFairy(void) : m_ShotTimeSum(0.f)
{
// 	m_Texture =  NNSpriteAtlas::Create(L"Sprite/warrior1_0.png");
// 	m_Texture->SetImageHeight(70.f);
// 	m_Texture->SetImageWidth(70.f);
// 	m_Texture->SetPosition(0.f, 0.f);
// 	AddChild( m_Texture );

	m_FairyMotion = NNAnimation::Create( 8, 0.3f,	
		L"Sprite/fairy1.png",
		L"Sprite/fairy2.png",
		L"Sprite/fairy3.png",
		L"Sprite/fairy4.png",
		L"Sprite/fairy5.png",
		L"Sprite/fairy6.png",
		L"Sprite/fairy7.png",
		L"Sprite/fairy8.png");

	m_FairyMotion->SetScale(1.5f, 1.5f);
	AddChild( m_FairyMotion );
}

CFairy::~CFairy(void)
{
}

void CFairy::Render()
{
	NNObject::Render();
}

void CFairy::Update( float dTime, CMaincharacter* Enemy)
{
	UpdateShotDirection(Enemy);
	UpdateShotPoint();

	NormalAttack(dTime);

	m_FairyMotion->Update(dTime);
	m_FairyMotion->SetRotation(GetShotDirection() + 90.f);
}

void CFairy::NormalAttack( float dTime )
{	
	m_ShotTimeSum += dTime;
	if (m_ShotTimeSum >= 2.f)
	{
		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(FAIRY_NORMAL_BULLET, FAIRY_NORMAL_BULLET_SPEED, GetShotDirection());
		pBullet->SetDirection(GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		m_ShotTimeSum = 0.f;
	}
}

void CFairy::SectorAttack( float dTime )
{
	float degree = 120.f;
	int n = 6;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(FAIRY_NORMAL_BULLET, 0, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->SetDirection(direction);
		pBullet->GetTexture(FAIRY_NORMAL_BULLET)->SetRotation(direction + 90.f);
	}
	m_ShotTimeSum = 0.f;
}



