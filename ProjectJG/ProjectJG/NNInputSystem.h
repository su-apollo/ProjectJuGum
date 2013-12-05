
#pragma once

#include "NNConfig.h"
#include "GameOption.h"

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
	void SetSkillKey(int skillnum, int skillkey) {m_skill[skillnum] = skillkey;}

	void UpdateKeyState();
	KeyState GetKeyState( int key );

	//여기서부터는 게임에 종속되는 부분(EInputSetUp은 프레임워크가아니라 게임에 속해있다.)
	EInputSetUp GetMainMenuInput(void);
	EInputSetUp GetDirectionKeyInput(void);
	EInputSetUp GetSkillKeyInput(void);
	EInputSetUp GetGameMenuKeyInput(void);
	EInputSetUp GetChangeSpeedKeyInput(void);

private:
	static NNInputSystem* m_pInstance;

	int m_keyup;
	int m_keydown;
	int m_keyleft;
	int m_keyright;

	int m_skill[6];

	int m_upgradekey;
	int m_changespeedkey;
	int m_pausekey;

	NNInputSystem();
	~NNInputSystem();


	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];
};


