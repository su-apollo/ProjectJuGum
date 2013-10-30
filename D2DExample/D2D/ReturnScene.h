
#pragma once
#include "NNScene.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNSceneDirector.h"
#include "MainMenuScene.h"

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

