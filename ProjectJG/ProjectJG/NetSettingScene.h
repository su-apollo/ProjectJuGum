#pragma once
#include "NNScene.h"

class NNLabel;

enum NetworkMode
{
	CLIENT_MODE,
	SERVER_MODE,
	NET_MENU_LAST
};

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

