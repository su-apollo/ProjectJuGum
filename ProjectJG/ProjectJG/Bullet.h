#pragma once
#include "NNCircle.h"
#include "GameOption.h"

class CMaincharacter;

class CBullet : public NNObject
{
public:
	CBullet(void);
	virtual ~CBullet(void);

	void Render();
	void Update( float dTime );
	float GetSpeed(){ return m_speed; }
	NNCircle * GetMainCircle(){return m_Circle;}

	void SetSpeed( float new_speed = BULLET_SPEED ){ m_speed = new_speed;}
	void SetDirection(float new_direction = 270.f){ m_direction = new_direction; }

	bool CharacterHitCheck(CMaincharacter * Player);

private:
	NNCircle* m_Circle;

	float m_speed;
	float m_direction;
};

