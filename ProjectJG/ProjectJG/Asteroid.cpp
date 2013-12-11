#include "NNConfig.h"
#include "Asteroid.h"
#include "NNSpriteAtlas.h"

CAsteroid::CAsteroid(void) : 
	m_HP(0)
{
	SetHitRadius(ASTEROID_HIT_RADIUS);

	m_Texture =  NNSpriteAtlas::Create(L"Sprite/asteroid.png");
	m_Texture->SetImageHeight(ASTEROID_HIT_RADIUS*2);
	m_Texture->SetImageWidth(ASTEROID_HIT_RADIUS*2);
	m_Texture->SetPosition(0.f, 0.f);
	AddChild( m_Texture );

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
