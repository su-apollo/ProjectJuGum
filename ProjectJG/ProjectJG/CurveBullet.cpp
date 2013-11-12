#include "CurveBullet.h"
#include "Maincharacter.h"


CCurveBullet::CCurveBullet(void)
{
	m_Circle = NNCircle::Create(10.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_direction = 270.f;
	m_speed = CURVEBULLET_SPEED;
	m_AngularAcceleration = 30.f;
}


CCurveBullet::~CCurveBullet(void)
{
}

void CCurveBullet::Render()
{
	NNObject::Render();
}

void CCurveBullet::Update( float dTime )
{
	m_direction += m_AngularAcceleration*dTime;
	float x = m_speed * NNDegreeToX(m_direction);
	float y = m_speed * NNDegreeToY(m_direction);
	SetPosition( GetPosition() + NNPoint(x, y) * dTime);
}

bool CCurveBullet::CharacterHitCheck( CMaincharacter * Player )
{
	if((m_Circle->GetRadius() + Player->GetMainCircle()->GetRadius()) 
					> GetPosition().GetDistance(Player->GetPosition()))
	{
		return true;
	}
	return false;
}
