#include "AccelBullet.h"

CAccelBullet::CAccelBullet(void)
{
	m_Circle = NNCircle::Create(20.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_direction = 270;
	m_speed = ACCELBULLET_SPEED;
	m_accelation = ACCELBULLET_ACCELERATION;
}

CAccelBullet::~CAccelBullet(void)
{
}

void CAccelBullet::Update( float dTime )
{
	m_speed += m_accelation;
	float x = m_speed * NNDegreeToX(m_direction);
	float y = m_speed * NNDegreeToY(m_direction);
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}

bool CAccelBullet::CharacterHitCheck(CMaincharacter * Player)
{
	if((m_Circle->GetRadius() + Player->GetMainCircle()->GetRadius()) 
					> GetPosition().GetDistance(Player->GetPosition()))
	{
		return true;
	}
	return false;
}

void CAccelBullet::Render()
{
	NNObject::Render();
}