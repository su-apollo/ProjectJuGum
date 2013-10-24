
#pragma once
#include "NNScene.h"
#include "NNLabel.h"

class CReturnScene :
	public NNScene
{
public:
	CReturnScene(void);
	virtual ~CReturnScene(void);

	void Render();
	void Update( float dTime );

	NNCREATE_FUNC(CReturnScene);

private:
	NNLabel* m_ReturnLabel;
	NNLabel* m_YesLabel;
	NNLabel* m_NoLabel;

	bool m_bReturn;
};

