#pragma once
#include "NNObject.h"

class CAsteroid 
	: public NNObject
{
public:
	CAsteroid(void);
	virtual ~CAsteroid(void);

	void		Render();
	void		Update( float dTime);
};

