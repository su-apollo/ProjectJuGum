#pragma once
#include "NNScene.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"

#include "NNApplication.h"
#include "Playtest.h"
#include "CustomObjectExample.h"


enum MENU_LIST
{
	MENU_PLAY,
	MENU_TEST,
	MENU_QUIT,
	MENU_LAST,
};

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
	NNLabel* m_MenuLabel[3];
	NNLabel* m_FPSLabel;
	
	wchar_t m_FPS[20];

	unsigned int m_KeyOn;
};

