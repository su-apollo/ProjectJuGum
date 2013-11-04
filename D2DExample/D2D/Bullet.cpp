#include "Bullet.h"


CBullet::CBullet(void)
{
	m_Circle = NNCircle::Create(20.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_speed = BULLET_SPEED;
	m_direction = 270;
}

CBullet::~CBullet(void)
{
}

void CBullet::Render()
{
	NNObject::Render();
}

void CBullet::Update( float dTime )
{
	float x = m_speed * NNDegreeToX(m_direction);
	float y = m_speed * NNDegreeToY(m_direction);
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}

bool CBullet::CharacterHitCheck(CMaincharacter * Player)
{
	if((m_Circle->GetRadius() + Player->GetMainCircle()->GetRadius()) 
					> GetPosition().GetDistance(Player->GetPosition()))
	{
		return true;
	}
	return false;
}