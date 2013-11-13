#pragma once
#include "Maincharacter.h"

class CMainMap;

class CFirstModeCharacter : public CMaincharacter
{
public:
	CFirstModeCharacter(void);
	virtual ~CFirstModeCharacter(void);

	void SkillCasting(CMaincharacter * Player, CMainMap * Map, float dTime);
};

