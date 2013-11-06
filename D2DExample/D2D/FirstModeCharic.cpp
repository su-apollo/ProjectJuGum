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
		if ( GetCost() >= SHOTBULLET*5 )
		{
			CBulletManager::GetInstance()->ShotSectorBullets(Player, 270, 90, 5);
			SetCost( GetCost() - SHOTBULLET*5 );
		}
		break;
	}
}