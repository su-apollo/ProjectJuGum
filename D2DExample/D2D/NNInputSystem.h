
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

	void SetKeyUp(int up){m_keyup = up;}
	void SetKeyDown(int down){m_keydown = down;}
	void SetKeyLeft(int left){m_keyleft = left;}
	void SetKeyRight(int right){m_keyright = right;}


	void UpdateKeyState();
	KeyState GetKeyState( int key );

	InputSetUp GetDirectionKeyInput(void);

private:
	static NNInputSystem* m_pInstance;

	int m_keyup;
	int m_keydown;
	int m_keyleft;
	int m_keyright;

	NNInputSystem();
	~NNInputSystem();


	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];
public:
	InputSetUp GetSkillKeyInput(void);
};


