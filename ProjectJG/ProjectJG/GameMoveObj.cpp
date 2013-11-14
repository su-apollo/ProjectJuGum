#include "NNConfig.h"
#include "GameMoveObj.h"

CGameMoveObj::CGameMoveObj(void) : 
	m_ShotDirection(0.f), m_Speed(0.f), 
	m_Accelation(0.f), m_Direction(0.f),
	m_HitRadius(0.f)
{
}


CGameMoveObj::~CGameMoveObj(void)
{
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

bool CGameMoveObj::HitCheck_CircleToCircle( CGameMoveObj * Enemy )
{
	if (Enemy->GetHitRadius() + GetHitRadius() > GetPosition().GetDistance(Enemy->GetPosition()))
	{
		return true;
	}
	
	return false;
}
