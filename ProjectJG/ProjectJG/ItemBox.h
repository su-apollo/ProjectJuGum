#pragma once
#include "GameMoveObj.h"

class NNAnimation;

class CItemBox
	: public CGameMoveObj
{
public:
	CItemBox(void);
	virtual ~CItemBox(void);

	void		Render();
	void		Update( float dTime);

private:
	NNAnimation*	m_FlyMotion;

};

