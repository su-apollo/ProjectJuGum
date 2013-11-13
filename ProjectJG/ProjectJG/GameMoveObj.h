#pragma once
#include "NNObject.h"

//게임상 모든 유동적인 오브젝트들의 정보를 가짐
class CGameMoveObj :
	public NNObject
{
public:
	CGameMoveObj(void);
	virtual ~CGameMoveObj(void);

	void UpdateShotDirection( CGameMoveObj* Enemy );
	bool HitCheck_CircleToCircle(CGameMoveObj * Enemy);

	float GetShotDirection() {return m_ShotDirection;}
	float GetSpeed() {return m_Speed;}
	float GetAccelation() {return m_Accelation;}
	float GetDirection() {return m_Direction;}
	float GetHitRadius() {return m_HitRadius;}

	void SetShotDirection(float new_shotdirection) {m_ShotDirection = new_shotdirection;}
	void SetSpeed(float new_speed) {m_Speed = new_speed;}
	void SetAceelation(float new_accelation) {m_Accelation = new_accelation;}
	void SetDirection(float new_direction) {m_Direction = new_direction;}
	void SetHitRadius(float new_hitRadius) {m_HitRadius = new_hitRadius;}

protected:
	float m_ShotDirection;
	float m_Speed;
	float m_Accelation;
	float m_Direction;
	float m_HitRadius;

};

