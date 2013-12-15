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

	void			Render();
	void			Update(float dTime, CMaincharacter* enemy);
	
	ECharState		GetState() const { return m_State; }
	void			SetState(ECharState val) { m_State = val; }

protected:
	ESubCharType	m_Type;
	ECharState		m_State;
	
	NNAnimation*	m_FlyMotion;
};

