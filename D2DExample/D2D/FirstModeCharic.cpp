#include "FirstModeCharic.h"

CFirstModeCharic::CFirstModeCharic(void) 
{

}

CFirstModeCharic::~CFirstModeCharic(void) 
{

}

void CFirstModeCharic::SkillCasting(CMaincharacter* Player, CMainMap* Map, float dTime)
{
	if (NNInputSystem::GetInstance()->GetKeyState('Z') == KEY_DOWN)
	{
		if ( GetCost() >= SHOTBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(Player);
			SetCost( GetCost() - SHOTBULLET_COST );
		}
	}
	else if (NNInputSystem::GetInstance()->GetKeyState('X') == KEY_DOWN)
	{
		if ( GetCost() >= SHOTACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotAccelBullet(Player);
			SetCost( GetCost() - SHOTACCELBULLET_COST );
		}
	}
}