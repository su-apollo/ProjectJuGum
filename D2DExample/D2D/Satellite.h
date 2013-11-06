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
	void		Update( float dTime );

	NNCircle *	GetMainCircle(){return m_Circle;}

private:
	NNCircle*	m_Circle;
	float		m_speed;
	int			m_direction;

};

