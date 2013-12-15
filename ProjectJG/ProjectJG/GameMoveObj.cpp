#include "NNConfig.h"
#include "GameMoveObj.h"

CGameMoveObj::CGameMoveObj(void) : 
	m_ShotDirection(0.f), m_Speed(0.f), 
	m_Accel(0.f), m_Direction(0.f),
	m_HitRadius(0.f), m_AngularAccel(0.f),
	m_LifeTime(0.f)
{
}


CGameMoveObj::~CGameMoveObj(void)
{
}

void CGameMoveObj::InitMember()
{
	m_ShotDirection = 0.f;
	m_Speed = 0.f;
	m_Accel = 0.f;
	m_Direction = 0.f;
	m_AngularAccel = 0.f;
	m_LifeTime = 0.f;
}

void CGameMoveObj::UpdateShotDirection( CGameMoveObj* Enemy )
{
	float x = GetPositionX() - Enemy->GetPositionX();
	float y = GetPositionY() - Enemy->GetPositionY();

	float d = Enemy->GetPosition().GetDistance(GetPosition());

	float cosdegree = NNRadianToDegree(acos( x/d ));
	float sindegree = NNRadianToDegree(asin( y/d ));

	if (x <= 0 && y <= 0)
	{
		m_ShotDirection = -sindegree;
	}
	else if (x >= 0 && y <= 0)
	{
		m_ShotDirection = sindegree + 180;
	}
	else if (x >= 0 && y >= 0)
	{
		m_ShotDirection = cosdegree + 180;
	}
	else if (x <= 0 && y >= 0)
	{
		m_ShotDirection = cosdegree + 180;
	}
}

void CGameMoveObj::UpdateShotPoint()
{
	m_ShotPoint = GetPosition();

	m_ShotPoint.SetX(GetPositionX() + SHOT_POINT*NNDegreeToX(m_ShotDirection));
	m_ShotPoint.SetY(GetPositionY() + SHOT_POINT*NNDegreeToY(m_ShotDirection));
}

bool CGameMoveObj::HitCheck_CircleToCircle( CGameMoveObj * Enemy )
{
	if (Enemy->GetHitRadius() + GetHitRadius() > GetPosition().GetDistance(Enemy->GetPosition()))
	{
		return true;
	}
	
	return false;
}
