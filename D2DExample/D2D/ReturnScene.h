#pragma once
#include "NNScene.h"

class NNLabel;

class CReturnScene :
	public NNScene
{
public:
	CReturnScene(void);
	virtual ~CReturnScene(void);

	void Render();
	void Update( float dTime );

private:
	NNLabel* m_ReturnLabel;
	NNLabel* m_YesLabel;
	NNLabel* m_NoLabel;

	bool m_bReturn;
};

