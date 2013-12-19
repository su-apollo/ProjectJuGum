#include "NNConfig.h"
#include "NNSprite.h"

#include "NNCircle.h"
#include "Bullet.h"
#include "Maincharacter.h"

CBullet::CBullet()
{
	//·¹ÀÌ¹« ÀÏ¹ÝÅºÈ¯
	m_Texture[RAYMU_NORMAL_BULLET] = NNSprite::Create(L"Sprite/BulletR1.png");
	m_Texture[RAYMU_NORMAL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[RAYMU_NORMAL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS*1.5f);
	m_Texture[RAYMU_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[RAYMU_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[RAYMU_NORMAL_BULLET]);

	//°¡¼ÓÅºÈ¯
	m_Texture[RAYMU_ACCEL_BULLET] = NNSprite::Create(L"Sprite/BulletR2.png");
	m_Texture[RAYMU_ACCEL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS);
	m_Texture[RAYMU_ACCEL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS*1.5f);
	m_Texture[RAYMU_ACCEL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[RAYMU_ACCEL_BULLET]->SetVisible(false);
	AddChild(m_Texture[RAYMU_ACCEL_BULLET]);

	//Ä¿ºêÅºÈ¯
	m_Texture[RAYMU_CURVE_BULLET] = NNSprite::Create(L"Sprite/BulletR3.png");
	m_Texture[RAYMU_CURVE_BULLET]->SetImageHeight(2*BULLET_CURVE_HIT_RADIUS);
	m_Texture[RAYMU_CURVE_BULLET]->SetImageWidth(2*BULLET_CURVE_HIT_RADIUS);
	m_Texture[RAYMU_CURVE_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[RAYMU_CURVE_BULLET]->SetVisible(false);
	AddChild(m_Texture[RAYMU_CURVE_BULLET]);

	//¸¶¸®»ç ÀÏ¹ÝÅºÈ¯
	m_Texture[MARISA_NORMAL_BULLET] = NNSprite::Create(L"Sprite/BulletB1.png");
	m_Texture[MARISA_NORMAL_BULLET]->SetImageHeight(3*BULLET_HIT_RADIUS);
	m_Texture[MARISA_NORMAL_BULLET]->SetImageWidth(3*BULLET_HIT_RADIUS);
	m_Texture[MARISA_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[MARISA_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[MARISA_NORMAL_BULLET]);

	//°¨¼ÓÅºÈ¯
	m_Texture[MARISA_RETAR_BULLET] = NNSprite::Create(L"Sprite/BulletB2.png");
	m_Texture[MARISA_RETAR_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS*1.6f);
	m_Texture[MARISA_RETAR_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[MARISA_RETAR_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[MARISA_RETAR_BULLET]->SetVisible(false);
	AddChild(m_Texture[MARISA_RETAR_BULLET]);

	//°Å´ëÅºÈ¯
	m_Texture[MARISA_BIG_BULLET] = NNSprite::Create(L"Sprite/BulletB3.png");
	m_Texture[MARISA_BIG_BULLET]->SetImageHeight(2*BULLET_BIG_HIT_RADIUS);
	m_Texture[MARISA_BIG_BULLET]->SetImageWidth(2*BULLET_BIG_HIT_RADIUS);
	m_Texture[MARISA_BIG_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[MARISA_BIG_BULLET]->SetVisible(false);
	AddChild(m_Texture[MARISA_BIG_BULLET]);

	//¿äÁ¤ ÀÏ¹ÝÅºÈ¯
	m_Texture[FAIRY_NORMAL_BULLET] = NNSprite::Create(L"Sprite/fairybullet.png");
	m_Texture[FAIRY_NORMAL_BULLET]->SetImageHeight(2*BULLET_HIT_RADIUS*1.6f);
	m_Texture[FAIRY_NORMAL_BULLET]->SetImageWidth(2*BULLET_HIT_RADIUS);
	m_Texture[FAIRY_NORMAL_BULLET]->SetPosition(0.f, 0.f);
	m_Texture[FAIRY_NORMAL_BULLET]->SetVisible(false);
	AddChild(m_Texture[FAIRY_NORMAL_BULLET]);

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
	SetLifeTime(dTime + GetLifeTime());

	if (m_Type == MARISA_NORMAL_BULLET || m_Type == RAYMU_CURVE_BULLET)
		m_Texture[m_Type]->SetRotation(100.f*GetLifeTime());

	if (GetAngularAccel())
		SetDirection(GetDirection() + GetAngularAccel()*dTime);

	if (GetAccel())
		SetSpeed(GetSpeed() + GetAccel()*dTime);

	float x = GetSpeed() * NNDegreeToX(GetDirection());
	float y = GetSpeed() * NNDegreeToY(GetDirection());

	SetPosition(GetPositionX()+x*dTime, GetPositionY()+y*dTime);
}
