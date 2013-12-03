#pragma once
#include "GameMoveObj.h"

class NNSpriteAtlas;
class CMaincharacter;

class CSatellite 
	: public CGameMoveObj
{
public:
	CSatellite(void);
	virtual ~CSatellite(void);

	void		Render();
	void		Update(float dTime, CMaincharacter* Enemy);

	void		ShotNomalBullet( float dTime);

private:
	NNSpriteAtlas*	m_Texture;
	float		m_dTimeSum;
};

