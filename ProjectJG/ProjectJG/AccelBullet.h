#pragma once
#include "NNCircle.h"
#include "GameOption.h"

class CMaincharacter;

// agebreak : 각각의 Bullet은 Bullet 클래스에서 상속받는 구조로 만드는것이 더 낫지 않을까??!!
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
	void SetDirection(float new_direction = 270.f){ m_direction = new_direction; }

private:
	NNCircle*	m_Circle;

	float		m_accelation;
	float		m_speed;
	float		m_dTimeSum;
	float		m_direction;
};

