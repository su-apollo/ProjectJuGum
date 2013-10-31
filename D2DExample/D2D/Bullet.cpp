#include "Bullet.h"


CBullet::CBullet(void)
{
	m_Circle = NNCircle::Create(5.f);
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
	SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(m_direction), m_speed*NNDegreeToY(m_direction))*dTime);
}