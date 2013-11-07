#pragma once
#include "NNObject.h"

class NNCircle;

class CSatellite 
	: public NNObject
{
public:
	CSatellite(void);
	virtual ~CSatellite(void);

	void		Render();
	void		Update( float dTime, CSatellite* Satellite);

	NNCircle *	GetMainCircle(){return m_Circle;}

	void		ShotNomalBullet( float dTime, CSatellite* Satellite);

private:
	NNCircle*	m_Circle;
	float		m_speed;
	float		m_dTimeSum;
	float		m_direction;

};

