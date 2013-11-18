#pragma once
#include "GameMoveObj.h"

class NNCircle;

class CAsteroid 
	: public CGameMoveObj
{
public:
	CAsteroid(void);
	virtual ~CAsteroid(void);

	void		Render();
	void		Update( float dTime);

	void		SetRandomSpeed();
	void		SetHP(int new_HP) {m_HP = new_HP;}

	int			GetHP() {return m_HP;}

private:
	int			m_HP;
	NNCircle*	m_Circle;

};

