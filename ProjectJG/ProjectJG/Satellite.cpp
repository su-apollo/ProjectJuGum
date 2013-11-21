#include "NNConfig.h"
#include "Satellite.h"
#include "NNCircle.h"
#include "BulletManager.h"
#include "Maincharacter.h"

CSatellite::CSatellite(void) : m_dTimeSum(0.f)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );
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


