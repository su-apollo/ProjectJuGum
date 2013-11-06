#include "NNInputSystem.h"

#include "FirstModeCharic.h"
#include "BulletManager.h"
#include "MainMap.h"


CFirstModeCharic::CFirstModeCharic(void) 
{

}

CFirstModeCharic::~CFirstModeCharic(void) 
{

}

void CFirstModeCharic::SkillCasting(CMaincharacter* Player, CMainMap* Map, float dTime)
{
	switch (NNInputSystem::GetInstance()->GetSkillKeyInput())
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= SHOTBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(Player);
			SetCost( GetCost() - SHOTBULLET_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SHOTACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotAccelBullet(Player);
			SetCost( GetCost() - SHOTACCELBULLET_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= SHOTBULLET_COST*7 )
		{
			CBulletManager::GetInstance()->ShotSectorNormalBullets(Player, 270, 90, 7);
			SetCost( GetCost() - SHOTBULLET_COST*7 );
		}
		break;
	case SKILL_KEY_FOUR:
		if ( GetCost() >= SHOTBULLET_COST*20 )
		{
			CBulletManager::GetInstance()->ShotSectorMixBullets(Player, 270, 180, 20);
			SetCost( GetCost() - SHOTBULLET_COST*20 );
		}
		break;
	case SKILL_KEY_FIVE:
		if ( GetCost() >= SETUPSATELLITE_COST )
		{
			CBulletManager::GetInstance()->ShotSetupSatellite(Player);
			SetCost(GetCost() - SETUPSATELLITE_COST);
		}
		break;
	}
}