#pragma once
#include "GameMoveObj.h"

class NNCircle;
class CMaincharacter;

class CSatellite 
	: public CGameMoveObj
{
public:
	CSatellite(void);
	virtual ~CSatellite(void);

	void		Render();
	void		Update(float dTime, CSatellite* Satellite, CMaincharacter* Enemy);

	NNCircle *	GetMainCircle(){return m_Circle;}

	void		ShotNomalBullet( float dTime, CSatellite* Satellite);

private:
	NNCircle*	m_Circle;
	float		m_dTimeSum;
};

