#pragma once
#include "Maincharacter.h"

class CMainMap;

// agebreak : FirstModeCharic 이라는 이름이 뭔가 간명하지 않음. 주석을 달거나 이름을 수정할 것
class CFirstModeCharic : public CMaincharacter
{
public:
	CFirstModeCharic(void);
	virtual ~CFirstModeCharic(void);

	void SkillCasting(CMaincharacter * Player, CMainMap * Map, float dTime);
};

