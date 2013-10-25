#pragma once
#include "NNCircle.h"

class CMaincharacter : public NNObject
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void Render();
	void Update( float dTime );
	float GetSpeed(){ return m_speed; };

	NNCREATE_FUNC(CMaincharacter);

private:
	NNCircle* m_Circle;
	float m_speed;
};

