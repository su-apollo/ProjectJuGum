#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"

class CMaincharacter;
class NNCircle;

class CBullet : public CGameMoveObj
{
public:
	CBullet(void);
	virtual ~CBullet(void);

	void Render();
	void Update( float dTime );

	EBulletType GetBulletType() {return m_Type;}
	NNCircle *	GetMainCircle() {return m_Circle;}

	void		SetBulletType(EBulletType new_type) {m_Type = new_type;}

private:
	NNCircle*	m_Circle;
	EBulletType	m_Type;
};

