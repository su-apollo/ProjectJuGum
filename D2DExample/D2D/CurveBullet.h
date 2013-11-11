#pragma once
#include "NNCircle.h"

class CMaincharacter;

class CCurveBullet:
	public NNObject
{
public:
	CCurveBullet(void);
	virtual ~CCurveBullet(void);

	void Render();
	void Update( float dTime );

	float GetSpeed(){ return m_speed; }
	NNCircle * GetMainCircle(){ return m_Circle; }

	bool CharacterHitCheck(CMaincharacter * Player);
	float GetAngularAcceleration(){ return m_AngularAcceleration; }

	void SetSpeed( float new_speed = BULLET_SPEED ){ m_speed = new_speed; }
	void SetAngularAcceleration( float new_accel = 30.f ){ m_AngularAcceleration = new_accel; }
	void SetDirection(float new_direction = 270.f){ m_direction = new_direction; }

private:
	NNCircle*	m_Circle;

	float		m_AngularAcceleration;
	float		m_speed;
	float		m_direction;
};

