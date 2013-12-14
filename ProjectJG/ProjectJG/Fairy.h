#pragma once
#include "GameMoveObj.h"

class NNSpriteAtlas;
class NNAnimation;
class CMaincharacter;

class CFairy
	: public CGameMoveObj
{
public:
	CFairy(void);
	virtual ~CFairy(void);

	void		Render();
	void		Update(float dTime, CMaincharacter* Enemy);

	void		NomalAttack( float dTime );

private:
	NNSpriteAtlas*	m_FairyTexture;
	NNAnimation*	m_FairyMotion;
	float			m_dTimeSum;
	
};

