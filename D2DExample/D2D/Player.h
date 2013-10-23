#pragma once
#include "NNCircle.h"

class CPlayer : public NNObject
{
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	void Render();
	void Update( float dTime );
	float GetSpeed(){ return m_speed; };

	NNCREATE_FUNC(CPlayer);

private:
	NNCircle* m_Circle;
	float m_speed;
};

