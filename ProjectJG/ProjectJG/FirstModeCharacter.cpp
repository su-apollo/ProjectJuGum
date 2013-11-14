#include "NNConfig.h"
#include "NNInputSystem.h"

#include "FirstModeCharacter.h"
#include "BulletManager.h"
#include "MainMap.h"

CFirstModeCharacter::CFirstModeCharacter(void) 
{
}

CFirstModeCharacter::~CFirstModeCharacter(void) 
{

}

void CFirstModeCharacter::SkillCasting(CMaincharacter* Player, CMainMap* Map, float dTime)
{
	switch (NNInputSystem::GetInstance()->GetSkillKeyInput())
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= SHOT_BULLET_COST )
		{
			CBulletManager::GetInstance()->ShotTBullet(Player);
			SetCost( GetCost() - SHOT_BULLET_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SHOT_ACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotAccelBullet(Player);
			SetCost( GetCost() - SHOT_ACCELBULLET_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= SECTOR_SINGLE_COST*20 )
		{
			CBulletManager::GetInstance()->ShotSectorMixBullets(Player);
			SetCost( GetCost() - SECTOR_SINGLE_COST*20 );
		}
		break;
	case SKILL_KEY_FOUR:
		if ( GetCost() >= TORNADO_SINGLE_COST*6 )
		{
			CBulletManager::GetInstance()->ShotTornadoBullets(Player, 6);
			SetCost( GetCost() - TORNADO_SINGLE_COST*6 );
		}
		break;
	case SKILL_KEY_FIVE:
		if ( GetCost() >= SETUP_SATELLITE_COST )
		{
			CBulletManager::GetInstance()->ShotSetupSatellite(Player);
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