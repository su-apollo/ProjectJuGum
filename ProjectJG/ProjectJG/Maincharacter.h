#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"
#include "NNPoint.h"

class NNCircle;
class CMainMap;
class NNSpriteAtlas;
class CSatellite;
class NNAnimation;
class CPacketHandler;

//메인케릭터 펙토리형태로 구성
class CMaincharacter : public CGameMoveObj
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void			Render();
	
	void			Update(float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode);
	void			UpdateByPeer(float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode);

	void			UpdateMotion(float dTime, EInputSetUp move_key);
	void			FirstStageSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key);
	bool			UpdateExplosionAnimation(float dTime);

	NNCircle *		GetMainCircle(){return m_Circle;}

	float			GetCost() {return m_Cost;}
	ECharcterStage  GetStage() {return m_Stage;}

	void			SetCost(float cost) {m_Cost = cost;}
	void			SetStage(ECharcterStage new_stage) {m_Stage = new_stage;}
	void			SkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key);

	void			SetHit( bool bHit ) { m_bHit = bHit; }
	bool			IsHit() { return m_bHit; }

	//인공위성 관련 스킬
	void			ShotSLSectorNormalBullet();
	void			SetupSatellite();
	void			UpdateSatellite(float dTime, CMaincharacter* Enemy);
	CSatellite**	GetSatelliteArray() { return m_pSatelliteArray; }
	CSatellite*		GetSatellite();
	void			DestroySatellite();

	//네트워크 관련 함수
	CPacketHandler* GetPacketHandler() { return m_PacketHandler; }

protected:
	NNSpriteAtlas*	m_Texture;
	NNCircle*		m_Circle;
	ECharcterStage  m_Stage;
	float			m_Cost;

	NNAnimation*	m_Animation;

	bool			m_bHit;

	CSatellite*		m_pSatelliteArray[MAX_SATELLITE_NUM];
	int				m_SatelliteIndex;

	//동기화를 위한 시간
	float			m_Syntime;
	EInputSetUp		m_skill_key_input;
	EInputSetUp		m_direct_key_input;
	EInputSetUp		m_speed_key_input;

	EInputSetUp		m_StateOfDirectionKey;
	EInputSetUp		m_StateOfSpeedKey;
	EInputSetUp		m_StateOfSkillKey;

	CPacketHandler* m_PacketHandler;
};

