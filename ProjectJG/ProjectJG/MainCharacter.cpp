#include "NNConfig.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "NNInputSystem.h"
#include "NNCircle.h"
#include "NNSpriteAtlas.h"

CMaincharacter::CMaincharacter(void)
{
	m_Texture =  NNSpriteAtlas::Create(L"Sprite/warrior2_0.png");
	AddChild( m_Texture );

	SetHitRadius(CHAR_HIT_RADIUS);
	m_Circle = NNCircle::Create(GetHitRadius());
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_Cost = 0;
	m_Stage = FIRST_STAGE_CHAR;
}

CMaincharacter::~CMaincharacter(void)
{
}

void CMaincharacter::Render()
{
	NNObject::Render();
}

void CMaincharacter::Update(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map)
{
	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateMotion(dTime);
	SkillCasting(dTime, player, enemy, map);
}

void CMaincharacter::UpdateMotion(float dTime)
{
	if (NNInputSystem::GetInstance()->GetChangeSpeedKeyInput() == CHANGE_SPEED)
	{
		SetSpeed(CHAR_FAST_SPEED);
	}
	else
	{
		SetSpeed(CHAR_SPEED);
	}

	//입력에 따른 캐릭터의 이동
	switch (NNInputSystem::GetInstance()->GetDirectionKeyInput())
	{
	case UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(270), GetSpeed()*NNDegreeToY(270)) * dTime );
		break;
	case DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(90), GetSpeed()*NNDegreeToY(90)) * dTime );
		break;
	case LEFT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(180), GetSpeed()*NNDegreeToY(180)) * dTime );
		break;
	case RIGHT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(0), GetSpeed()*NNDegreeToY(0)) * dTime );
		break;
	case LEFT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(225), GetSpeed()*NNDegreeToY(225))*dTime );
		break;
	case LEFT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(135), GetSpeed()*NNDegreeToY(135)) * dTime );
		break;
	case RIGHT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(315), GetSpeed()*NNDegreeToY(315))* dTime );
		break;
	case RIGHT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(45), GetSpeed()*NNDegreeToY(45)) * dTime );
		break;
	default:
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////////
//								 skillcasting									 //
///////////////////////////////////////////////////////////////////////////////////

void CMaincharacter::SkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map)
{
	switch (GetStage())
	{
	case FIRST_STAGE_CHAR:
		FirstStageSkillCasting(dTime, player, enemy, map);
		break;
	default:
		break;
	}
}

void CMaincharacter::FirstStageSkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map)
{
	switch (NNInputSystem::GetInstance()->GetSkillKeyInput())
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= SHOT_BULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(player, NORMAL_BULLET);
			SetCost( GetCost() - SHOT_BULLET_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SHOT_ACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(player, ACCEL_BULLET);
			SetCost( GetCost() - SHOT_ACCELBULLET_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= SECTOR_SINGLE_COST*20 )
		{
			CBulletManager::GetInstance()->ShotSectorMixBullets(player, ACCEL_BULLET, NORMAL_BULLET);
			SetCost( GetCost() - SECTOR_SINGLE_COST*20 );
		}
		break;
	case SKILL_KEY_FOUR:
		if ( GetCost() >= TORNADO_SINGLE_COST*6 )
		{
			CBulletManager::GetInstance()->ShotTornadoBullets(player, 6);
			SetCost( GetCost() - TORNADO_SINGLE_COST*6 );
		}
		break;
	case SKILL_KEY_FIVE:
		if ( GetCost() >= SETUP_SATELLITE_COST )
		{
			CBulletManager::GetInstance()->ShotSetupSatellite(player);
			SetCost(GetCost() - SETUP_SATELLITE_COST);
		}
		break;
	case SKILL_KEY_SIX:
		if (GetCost() >= SL_SECTORNORMAL_COST)
		{
			CBulletManager::GetInstance()->ShotSLSectorNormalBullet();
			SetCost(GetCost() - SL_SECTORNORMAL_COST);
		}
		break;
	}
}
