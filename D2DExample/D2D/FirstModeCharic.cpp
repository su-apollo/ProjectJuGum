#include "FirstModeCharic.h"

void CFirstModeCharic::SkillCasting(CMaincharacter * Player)
{
	if (NNInputSystem::GetInstance()->GetKeyState(VK_SHIFT) == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotBullet(Player);
	}
	if (NNInputSystem::GetInstance()->GetKeyState('Z') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->BulletShowerShot(Player);
	}
}