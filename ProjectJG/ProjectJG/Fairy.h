#pragma once
#include "GameMoveObj.h"

class NNSpriteAtlas;
class NNAnimation;
class CMaincharacter;
class NNSound;

class CFairy
	: public CGameMoveObj
{
public:
	CFairy(void);
	virtual ~CFairy(void);

	void		Render();
	void		Update(float dTime, CMaincharacter* Enemy);

	void		NormalAttack( float dTime );
	void		SectorAttack( float dTime );

private:
	NNSpriteAtlas*	m_FairyTexture;
	NNAnimation*	m_FairyMotion;
	float			m_ShotTimeSum;
	
	NNSound*		m_Shotsound;
};

