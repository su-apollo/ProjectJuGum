#pragma once
#include "NNCircle.h"

class CMaincharacter : public NNObject
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void Render();
	void Update( float dTime );

	float GetSpeed(){ return m_speed; }

	void SetSpeed( float new_speed ){ m_speed = new_speed;}
	void SetKeyUp(int up){m_keyup = up;}
	void SetKeyDown(int down){m_keydown = down;}
	void SetKeyLeft(int left){m_keyleft = left;}
	void SetKeyRight(int right){m_keyright = right;}

	NNCREATE_FUNC(CMaincharacter);

private:
	NNCircle* m_Circle;
	float m_speed;
	int m_keyup;
	int m_keydown;
	int m_keyleft;
	int m_keyright;
};

