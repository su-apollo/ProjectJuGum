#pragma once
#include "NNScene.h"
#include "NNLabel.h"
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

	NNLabel* m_LogoLabelEnglish;
	NNLabel* m_LogoLabelKorean;
	NNLabel* m_PlayMenuLabel;
	NNLabel* m_TestMenuLabel;
	NNLabel* m_QuitMenuLabel;
	NNLabel* m_MenuLabel[3];
	NNLabel* m_FPSLabel;
	
	wchar_t m_FPS[20];

	int m_KeyOn;
};

