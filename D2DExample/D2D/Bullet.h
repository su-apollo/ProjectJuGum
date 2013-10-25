#pragma once
#include "NNCircle.h"

class CBullet : public NNObject
{
public:
	CBullet(void);
	virtual ~CBullet(void);

	void Render();
	void Update( float dTime );
	float GetSpeed(){ return m_speed; };

	NNCREATE_FUNC(CBullet);

private:
	NNCircle* m_Circle;

	float m_speed;
	int m_direction;
};

