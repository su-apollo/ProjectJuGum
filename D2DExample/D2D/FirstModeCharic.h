#pragma once
#include "BulletManager.h"
#include "Maincharacter.h"

class CFirstModeCharic : public CMaincharacter
{
public:
	CFirstModeCharic(void) {}
	virtual ~CFirstModeCharic(void) {}

	void SkillCasting(CMaincharacter * Player);
};

