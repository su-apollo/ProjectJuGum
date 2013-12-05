#include "NNConfig.h"
#include "NNSpriteAtlas.h"

#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"


CBullet::CBullet(void)
{
	m_Texture[NORMAL_BULLET] = NNSpriteAtlas::Create(L"Sprite/coloredspheres/sphere-04.png");
	m_Texture[NORMAL_BULLET]->SetRenderCutImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[NORMAL_BULLET]->SetRenderCutImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[NORMAL_BULLET]);

	m_Texture[ACCEL_BULLET] = NNSpriteAtlas::Create(L"Sprite/coloredspheres/sphere-16.png");
	m_Texture[ACCEL_BULLET]->SetRenderCutImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[ACCEL_BULLET]->SetRenderCutImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[ACCEL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[ACCEL_BULLET]->SetVisible(false);
	AddChild(m_Texture[ACCEL_BULLET]);

	m_Texture[CURVE_BULLET] = NNSpriteAtlas::Create(L"Sprite/coloredspheres/sphere-14.png");
	m_Texture[CURVE_BULLET]->SetRenderCutImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[CURVE_BULLET]->SetRenderCutImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[CURVE_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[CURVE_BULLET]->SetVisible(false);
	AddChild(m_Texture[CURVE_BULLET]);

	SetHitRadius(BULLET_HIT_RADIUS);
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
