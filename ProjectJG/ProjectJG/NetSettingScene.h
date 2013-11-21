#pragma once
#include "NNScene.h"
#include "GameOption.h"

class NNLabel;

class CNetSettingScene
	: public NNScene
{
public:
	CNetSettingScene(void);
	virtual ~CNetSettingScene(void);

	void Render();
	void Update( float dTime );


private:
	NNLabel* m_MenuLabel[2];
	NNLabel* m_Wait;
	NNLabel* m_Error;

	unsigned int m_KeyOn;
};

