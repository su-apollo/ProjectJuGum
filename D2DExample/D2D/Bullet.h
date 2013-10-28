#pragma once
#include "NNCircle.h"

class CBullet : public NNObject
{
public:
	CBullet(void);
	virtual ~CBullet(void);

	void Render();
	void Update( float dTime );
	float GetSpeed(){ return m_speed; }
	NNCircle * GetMainCircle(){return m_Circle;}

	void SetSpeed( float new_speed ){ m_speed = new_speed;}
	void SetDirection(int new_direction){ m_direction = new_direction; }

	NNCREATE_FUNC(CBullet);

private:
	NNCircle* m_Circle;

	float m_speed;
	int m_direction;
};

