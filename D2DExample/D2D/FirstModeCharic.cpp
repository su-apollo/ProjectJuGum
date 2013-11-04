#include "FirstModeCharic.h"

CFirstModeCharic::CFirstModeCharic(void) 
{

}

CFirstModeCharic::~CFirstModeCharic(void) 
{

}

void CFirstModeCharic::SkillCasting(CMaincharacter * Player, CMainMap * Map, float dTime)
{
	if (NNInputSystem::GetInstance()->GetKeyState(VK_SHIFT) == KEY_DOWN)
	{
		if ( GetCost() >= SHOTBULLETCOST )
		{
			CBulletManager::GetInstance()->ShotBullet(Player);
			SetCost( GetCost() - SHOTBULLETCOST );
		}
	}
	if (NNInputSystem::GetInstance()->GetKeyState('Z') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->BulletShowerShot(Player);
	}
}