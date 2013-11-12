#pragma once
#include "NNConfig.h"

class CBullet;
class CMainMap;
class CAccelBullet;
class CCurveBullet;
class CMaincharacter;
class CSatellite;
class NNObject;

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//스킬들
	void ShotAccelBullet(NNObject * Player);
	void ShotBullet(NNObject * Player);
	void ShotCurveBullet(NNObject * Player);
	void ShotSectorNormalBullets( NNObject* Player, float direction = 270.f, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(NNObject* Player, float direction = 270.f, float degree = 180.f, int n = 20);
	void ShotTornadoBullets(NNObject* Player, int n);
	void ShotSetupSatellite(NNObject* Player);

	void ShotTBullet( NNObject* Player, float direction = 270.f, float degree =  90.f, int n = 3 );

	void ShotSLSectorNormalBullet();

	void UpdateObj(float dTime);
	void UpdateBullet(float dTime);
	void UpdateSatellite(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);

	void CheckBulletLifeTime(CMainMap * Map);
	void CheckSatelliteLifeTime();

	void DestroyBullet(CBullet* Bullet);
	void DestroyAccelBullet(CAccelBullet* Bullet);
	void DestroyCurveBullet(CCurveBullet* Bullet);
	void DestroySatellite(CSatellite* Satellite);
	
	//생산은 씬에서 해줘야함 불렛메니져는 생산된 불렛을 어레이로 보관하고 관리
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CAccelBullet ** GetAccelBulletArray() { return m_pAccelBulletArray; }
	CCurveBullet**	GetCurveBulletArray() { return m_pCurveBulletArray; }
	CSatellite **	GetSatelliteArray() { return m_pSatelliteArray; }
	

private:
	static CBulletManager * m_pInstance;

	// agebreak : 각각의 Bullet들의 부모 클래스를 Bullet으로 만들고, 상속 구조로 만들면 하나의 리스트에서 관리할 수 있지 않을까?!
	// 이런 구조라면 나중에 새로운 Bullet 타입이 추가될 때 마다, 변수와 함수들이 추가되어야 하는 문제가 있음.
	
	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CAccelBullet *	m_pAccelBulletArray[MAX_ACCELBULLET_NUM];
	CCurveBullet*	m_pCurveBulletArray[MAX_CURVEBULLET_NUM];
	CSatellite *	m_pSatelliteArray[MAX_SATELLITE_NUM];
	int				m_BulletIndex;
	int				m_AccelBulletIndex;
	int				m_CurveBulletIndex;
	int				m_SatelliteIndex;

	// agebreak : 그러면 이런 함수들과 구조도 훨씬 깔끔한 구조로 변경이 가능할 것 같은데?
	// Bullet 객체에서 상속을 받고, 각각의 Bullet 클래스에 BulletType을 enum 값으로 선언하여 구별하면 훨씬 좋은 구조가 될듯
	void			BulletLifeTime(CMainMap * Map, CBullet * Bullet);
	void			AccelBulletLifeTime(CMainMap * Map, CAccelBullet * Bullet);
	void			CurveBulletLifeTime(CMainMap* Map, CCurveBullet* Bullet);

	CBullet *		GetBullet();
	CAccelBullet *	GetAccelBullet();
	CCurveBullet*	GetCurveBullet();
	CSatellite *	GetSatellite();

};
