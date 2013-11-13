#pragma once
#include "NNCircle.h"
#include "GameOption.h"

class CMaincharacter : public NNObject
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void		Render();
	void		Update( float dTime );

	float		GetSpeed(){ return m_speed; }
	NNCircle *	GetMainCircle(){return m_Circle;}

	void		SetSpeed( float new_speed = CHAR_SPEED ){ m_speed = new_speed;}

	float		GetCost() {return m_Cost;}
	void		SetCost(float cost) {m_Cost = cost;}

protected:
	NNCircle*	m_Circle;
	float		m_speed;
	float		m_Cost;

	void		UpdateMotion(float dTime);
};

