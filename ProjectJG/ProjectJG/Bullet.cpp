#include "NNConfig.h"
#include "NNSpriteAtlas.h"

#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"


CBullet::CBullet(void)
{
	m_Texture = NNSpriteAtlas::Create(L"Sprite/coloredspheres/sphere-04.png");
	m_Texture->SetRenderCutImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture->SetRenderCutImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture->SetPosition(0.f, 0.f);
	AddChild(m_Texture);

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
