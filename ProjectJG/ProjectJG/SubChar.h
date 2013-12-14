#pragma once
#include "GameMoveObj.h"

class CMaincharacter;
class NNAnimation;

class CSubChar :
	public CGameMoveObj
{
public:
	CSubChar(ESubCharType type_of_char);
	virtual ~CSubChar(void);

	void		Render();
	void		Update(float dTime, CMaincharacter* Enemy);

	ESubCharType m_Type;
	NNAnimation* m_FlyMotion;
};

