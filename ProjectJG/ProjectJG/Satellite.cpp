#include "NNConfig.h"
#include "Satellite.h"
#include "NNCircle.h"
#include "BulletManager.h"
#include "Maincharacter.h"
#include "NNSpriteAtlas.h"

CSatellite::CSatellite(void) : m_dTimeSum(0.f)
{
	m_Texture =  NNSpriteAtlas::Create(L"Sprite/warrior1_0.png");
	m_Texture->SetImageHeight(70.f);
	m_Texture->SetImageWidth(70.f);
	m_Texture->SetPosition(0.f, 0.f);
	AddChild( m_Texture );
}


CSatellite::~CSatellite(void)
{
}

void CSatellite::Render()
{
	NNObject::Render();
}

void CSatellite::Update( float dTime, CMaincharacter* Enemy)
{
	UpdateShotDirection(Enemy);
	UpdateShotPoint();
	ShotNomalBullet(dTime);

	m_Texture->SetRotation(GetShotDirection());
}
 
void CSatellite::ShotNomalBullet( float dTime)
{
	m_dTimeSum += dTime;
	if (m_dTimeSum >= 2.f)
	{
		CBulletManager::GetInstance()->ShotBullet(this, NORMAL_BULLET);
		m_dTimeSum = 0.f;
	}
}


