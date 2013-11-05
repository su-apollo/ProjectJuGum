#pragma once
#include "NNObject.h"
#include "Maincharacter.h"

class CAccelBullet :
	public NNObject
{
public:
	CAccelBullet(void);
	virtual ~CAccelBullet(void);

	void Render();
	void Update( float dTime );

	float GetSpeed(){ return m_speed; }
	NNCircle * GetMainCircle(){return m_Circle;}

	bool CharacterHitCheck(CMaincharacter * Player);
	float GetAcceleration(){ return m_accelation; }

	void SetSpeed( float new_speed = ACCELBULLET_SPEED ){ m_speed = new_speed;}
	void SetAccelation( float new_accel = 0 ){ m_accelation = new_accel; }
	void SetDirection(int new_direction){ m_direction = new_direction; }

private:
	NNCircle*	m_Circle;

	float		m_accelation;
	float		m_speed;
	int			m_direction;
};

