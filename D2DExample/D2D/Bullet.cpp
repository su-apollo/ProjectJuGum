#include "Bullet.h"


CBullet::CBullet(void)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 100.f);
	AddChild( m_Circle );

	m_speed = 50.f;
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
	SetPosition( GetPosition() + NNPoint(0.f,-m_speed) * dTime );
}