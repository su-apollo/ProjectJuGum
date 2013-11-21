#include "NNConfig.h"
#include "Asteroid.h"
#include "NNCircle.h"

CAsteroid::CAsteroid(void) : 
	m_HP(0)
{
	SetHitRadius(30.f);
	m_Circle = NNCircle::Create(GetHitRadius());
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	SetDirection(135.f);
}


CAsteroid::~CAsteroid(void)
{
}

void CAsteroid::Render()
{
	NNObject::Render();
}

void CAsteroid::Update( float dTime )
{
	float x = GetSpeed() * NNDegreeToX(GetDirection());
	float y = GetSpeed() * NNDegreeToY(GetDirection());
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}

void CAsteroid::SetRandomSpeed()
{
	SetSpeed((float)(rand()%10+1)*50);
}
