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

	// agebreak : 각 총알 클래스에서 비슷한 함수를 계속 구현하면서, 뭔자 문제가 있다는 냄새가 나지 않았는가?
	// BulletManager.h의 주석을 참조할것
	void SetSpeed( float new_speed = BULLET_SPEED ){ m_speed = new_speed; }
	void SetAngularAcceleration( float new_accel = 30.f ){ m_AngularAcceleration = new_accel; }
	void SetDirection(float new_direction = 270.f){ m_direction = new_direction; }

private:
	NNCircle*	m_Circle;

	float		m_AngularAcceleration;
	float		m_speed;
	float		m_direction;
};

