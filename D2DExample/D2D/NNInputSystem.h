
#pragma once

#include "NNConfig.h"

/* */
/* NNInputSystem
/* 키 입력을 담당하는 싱글톤 클래스
/* */

enum KeyState
{
	KEY_DOWN,
	KEY_PRESSED,
	KEY_UP,
	KEY_NOTPRESSED,
};

class NNInputSystem
{

public:
	static NNInputSystem* GetInstance();
	static void ReleaseInstance();

public:
	void UpdateKeyState();
	KeyState GetKeyState( int key );


private:
	static NNInputSystem* m_pInstance;

private:
	NNInputSystem();
	~NNInputSystem();

private:
	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];
};


