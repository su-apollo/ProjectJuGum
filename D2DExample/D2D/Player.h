#pragma once
#include "NNCircle.h"

class CPlayer : public NNObject
{
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	void Render();
	void Update( float dTime );

	NNCREATE_FUNC(CPlayer);

private:
	NNCircle* m_Circle;

};

