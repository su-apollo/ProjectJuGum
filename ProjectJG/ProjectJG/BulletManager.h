#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
class NNObject;
class CGameMoveObj;
class CAsteroid;

//총알뿐만아니라 게임상의 모든 이동하는 오브젝트를 관리
//지금은 스킬도 관리중
class CBulletManager
{
public:
	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//스킬들
// 	void ShotBullet(CGameMoveObj* Player, EBulletType bullet_type);
// 	void ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree = 90.f, int n = 7);
// 	void ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree = 180.f, int n = 20);
// 	void ShotTornadoBullets(CGameMoveObj* Player, int n);

	//탄환이 맵밖으로 나갔는지 확인
	void			CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj);

	//메니져에게서 탄환을 받아오는 함수들
	CBullet*		GetBullet( EBulletType bullet_type, float speed, float direction );
	CAsteroid*		GetAsteroid();

	//운석출현 스킬
	void ShotAsteroid(CMainMap* Map);

	//업데이트
	void UpdateObj(float dTime , CMaincharacter* Enemy, CMainMap* Map);
	void UpdateBullet(float dTime, CMainMap* Map);
	void UpdateAsteroid(float dTime, CMainMap* Map);

	//히트채크
	bool CharacterHitCheck(CMaincharacter * Player);

	//라이프타임
	void DestroyObj(CGameMoveObj* Obj);
	
	//생산은 씬에서 해줘야함 불렛메니져는 생산된 불렛을 어레이로 보관하고 관리
	CBullet**		GetBulletArray() { return m_pBulletArray; }
	CAsteroid**		GetAsteroidArray() { return m_pAsteroidArray; }

private:
	static CBulletManager * m_pInstance;

	CBulletManager(void);
	virtual ~CBulletManager(void);
	
	CBullet*		m_pBulletArray[MAX_BULLET_NUM];
	CAsteroid*		m_pAsteroidArray[MAX_ASTEROID_NUM];
	int				m_BulletIndex;
	int				m_AsteroidIndex;

	

};
