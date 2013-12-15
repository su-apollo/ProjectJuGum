#pragma once
#include "NNObject.h"
#include "GameOption.h"

//게임상 모든 유동적인 오브젝트들의 정보를 가짐
class CGameMoveObj :
	public NNObject
{
public:
	CGameMoveObj(void);
	virtual ~CGameMoveObj(void);

	void	InitMember();

	void	UpdateShotDirection( CGameMoveObj* Enemy );
	bool	HitCheck_CircleToCircle(CGameMoveObj * Enemy);

	float	GetShotDirection() {return m_ShotDirection;}
	float	GetSpeed() {return m_Speed;}
	float	GetAccel() {return m_Accel;}
	float	GetDirection() {return m_Direction;}
	float	GetHitRadius() {return m_HitRadius;}
	float	GetAngularAccel() {return m_AngularAccel;}
	float	GetLifeTime() const { return m_LifeTime; }
	NNPoint	GetShotPoint() {return m_ShotPoint;}

	void	SetShotDirection(float new_shotdirection) {m_ShotDirection = new_shotdirection;}
	void	SetSpeed(float new_speed) {m_Speed = new_speed;}
	void	SetAccel(float new_accel) {m_Accel = new_accel;}
	void	SetDirection(float new_direction) {m_Direction = new_direction;}
	void	SetHitRadius(float new_hitRadius) {m_HitRadius = new_hitRadius;}
	void	SetAngularAccel(float new_accel) {m_AngularAccel = new_accel;}
	void	SetLifeTime(float val) { m_LifeTime = val; }

	void	UpdateShotPoint();

protected:
	float	m_ShotDirection;
	float	m_Speed;
	float	m_Accel;
	float	m_Direction;
	float	m_HitRadius;
	float	m_AngularAccel;
	float	m_LifeTime;
	
	
	NNPoint	m_ShotPoint;

};

