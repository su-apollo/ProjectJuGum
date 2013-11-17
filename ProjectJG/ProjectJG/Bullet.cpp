#include "NNConfig.h"
#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"

CBullet::CBullet(void)
{
	SetHitRadius(BULLET_HIT_RADIUS);
	m_Circle = NNCircle::Create(GetHitRadius());
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	SetDirection(270.f);
	SetSpeed(BULLET_SPEED);
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
	if (GetAngularAccel())
	{
		SetDirection(GetDirection() + GetAngularAccel()*dTime);
	}
	if (GetAccel())
	{
		SetSpeed(GetSpeed() + GetAccel()*dTime);
	}

	float x = GetSpeed() * NNDegreeToX(GetDirection());
	float y = GetSpeed() * NNDegreeToY(GetDirection());
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}