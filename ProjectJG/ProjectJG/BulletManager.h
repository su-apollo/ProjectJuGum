#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
class CSatellite;
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
	void ShotBullet(CGameMoveObj* Player, EBulletType bullet_type);
	void ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree = 180.f, int n = 20);
	void ShotTornadoBullets(CGameMoveObj* Player, int n);
	void ShotSetupSatellite(CGameMoveObj* Player);

	//인공위성 관련 스킬
	void ShotSLSectorNormalBullet();

	//운석출현 스킬
	void ShotAsteroid(CMainMap* Map);

	//업데이트
	void UpdateObj(float dTime , CMaincharacter* Enemy, CMainMap* Map);
	void UpdateBullet(float dTime, CMainMap* Map);
	void UpdateSatellite(float dTime , CMaincharacter* Enemy);
	void UpdateAsteroid(float dTime, CMainMap* Map);

	//히트채크
	bool CharacterHitCheck(CMaincharacter * Player);

	//라이프타임
	void DestroySatellite();
	void DestroyObj(CGameMoveObj* Obj);
	
	//생산은 씬에서 해줘야함 불렛메니져는 생산된 불렛을 어레이로 보관하고 관리
	CBullet**		GetBulletArray() { return m_pBulletArray; }
	CSatellite**	GetSatelliteArray() { return m_pSatelliteArray; }
	CAsteroid**		GetAsteroidArray() { return m_pAsteroidArray; }

private:
	static CBulletManager * m_pInstance;

	CBulletManager(void);
	virtual ~CBulletManager(void);
	
	CBullet*		m_pBulletArray[MAX_BULLET_NUM];
	CSatellite*		m_pSatelliteArray[MAX_SATELLITE_NUM];
	CAsteroid*		m_pAsteroidArray[MAX_ASTEROID_NUM];
	int				m_BulletIndex;
	int				m_SatelliteIndex;
	int				m_AsteroidIndex;

	void			CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj);

	CBullet*		GetBullet(EBulletType bullet_type);
	CSatellite*		GetSatellite();
	CAsteroid*		GetAsteroid();

};
