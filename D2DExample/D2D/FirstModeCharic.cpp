#include "FirstModeCharic.h"

void CFirstModeCharic::SkillCasting(CMaincharacter * Player)
{
	if (NNInputSystem::GetInstance()->GetKeyState(VK_SHIFT) == KEY_DOWN)
	{
		if ( GetCost() > 0 )
		{
			CBulletManager::GetInstance()->ShotBullet(Player);
			SetCost( GetCost() -1 );
		}
	}
	if (NNInputSystem::GetInstance()->GetKeyState('Z') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->BulletShowerShot(Player);
	}
}