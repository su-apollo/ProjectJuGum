#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"

class CMaincharacter;
class NNCircle;
class NNSpriteAtlas;

class CBullet : public CGameMoveObj
{
public:
	CBullet(void);
	CBullet(EBulletType type);
	virtual ~CBullet(void);

	void Render();
	void Update( float dTime );

	EBulletType		GetBulletType() {return m_Type;}
	NNSpriteAtlas*	GetTexture(EBulletType type) { return m_Texture[type]; }

	void			SetBulletType(EBulletType new_type) {m_Type = new_type;}

private:
	NNSpriteAtlas*	m_Texture[BULLET_TYPE_NUM];
	EBulletType		m_Type;
	bool			m_IsSpin;
};

