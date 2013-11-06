#pragma once
#include "Maincharacter.h"

class CMainMap;

class CFirstModeCharic : public CMaincharacter
{
public:
	CFirstModeCharic(void);
	virtual ~CFirstModeCharic(void);

	void SkillCasting(CMaincharacter * Player, CMainMap * Map, float dTime);
};

