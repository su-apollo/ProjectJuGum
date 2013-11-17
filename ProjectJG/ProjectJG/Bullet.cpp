#include "NNConfig.h"
#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"

CBullet::CBullet(void)
{
	m_Circle = NNCircle::Create(10.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_speed = BULLET_SPEED;
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
	if (!GetAngularAccel())
	{
		SetDirection(GetDirection() + GetAngularAccel()*dTime);
	}
	if (!GetAccel())
	{
		SetSpeed(GetSpeed() + GetAccel()*dTime);
	}

	float x = m_speed * NNDegreeToX(m_direction);
	float y = m_speed * NNDegreeToY(m_direction);
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}