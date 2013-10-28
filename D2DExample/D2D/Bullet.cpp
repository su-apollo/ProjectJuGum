#include "Bullet.h"


CBullet::CBullet(void)
{
	m_Circle = NNCircle::Create(20.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_speed = 500.f;
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
	SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(m_direction), m_speed*NNAngleToY(m_direction))*dTime);
}