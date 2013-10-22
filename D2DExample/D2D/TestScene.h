#pragma once
#include "NNScene.h"
#include "NNLabel.h"
#include "NNObject.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"

class CTestScene : public NNScene
{
public:
	CTestScene(void);
	virtual ~CTestScene(void);

	void Render();
	void Update( float dTime );

	NNCREATE_FUNC(CTestScene);

private:
	NNObject m_testobject;

	NNLabel* m_DifferentFontLabel;
};

