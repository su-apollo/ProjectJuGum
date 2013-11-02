#pragma once
#include "NNInputSystem.h"

enum Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	WRONG_INPUT
};

class CInputManager
{
public:
	
	~CInputManager(void);

	void SetKeyUp(int up){m_keyup = up;}
	void SetKeyDown(int down){m_keydown = down;}
	void SetKeyLeft(int left){m_keyleft = left;}
	void SetKeyRight(int right){m_keyright = right;}
	
	Directions GetDirectionKeyInput(void);



protected:
	CInputManager(void);

private:	
	int m_keyup;
	int m_keydown;
	int m_keyleft;
	int m_keyright;

	static CInputManager* pInstance;

	
public:
	static CInputManager* getInstance();
};

