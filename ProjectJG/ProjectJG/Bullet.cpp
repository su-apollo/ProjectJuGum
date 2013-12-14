#include "NNConfig.h"
#include "NNSpriteAtlas.h"

#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"

CBullet::CBullet()
{
	m_Texture[RAYMU_NORMAL_BULLET] = NNSpriteAtlas::Create(L"Sprite/BulletR1.png");
	m_Texture[RAYMU_NORMAL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS*1.5f);
	m_Texture[RAYMU_NORMAL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[RAYMU_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[RAYMU_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[RAYMU_NORMAL_BULLET]);

	m_Texture[MARISA_NORMAL_BULLET] = NNSpriteAtlas::Create(L"Sprite/BulletB1.png");
	m_Texture[MARISA_NORMAL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[MARISA_NORMAL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[MARISA_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[MARISA_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[MARISA_NORMAL_BULLET]);

	m_Texture[FAIRY_NORMAL_BULLET] = NNSpriteAtlas::Create(L"Sprite/fairybullet.png");
	m_Texture[FAIRY_NORMAL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS*1.5f);
	m_Texture[FAIRY_NORMAL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[FAIRY_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[FAIRY_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[FAIRY_NORMAL_BULLET]);

	SetHitRadius(BULLET_HIT_RADIUS);
	SetDirection(270.f);
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
