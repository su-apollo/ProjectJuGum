#include "Maincharacter.h"
#include "BulletManager.h"
#include "NNInputSystem.h"

CMaincharacter::CMaincharacter(void)
{
	m_Circle = NNCircle::Create(5.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_speed = CHARIC_SPEED;
}

CMaincharacter::~CMaincharacter(void)
{
}

void CMaincharacter::Render()
{
	NNObject::Render();
}

void CMaincharacter::Update( float dTime )
{
	UpdateMotion(dTime);
}

void CMaincharacter::UpdateMotion(float dTime)
{
	
	if (NNInputSystem::GetInstance()->GetChangeSpeedKeyInput() == CHANGE_SPEED)
	{
		m_speed = CHARIC_FAST_SPEED;
	}
	else
	{
		m_speed = CHARIC_SPEED;
	}

	//입력에 따른 캐릭터의 이동
	switch (NNInputSystem::GetInstance()->GetDirectionKeyInput())
	{
	case UP:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(270), m_speed*NNDegreeToY(270)) * dTime );
		break;
	case DOWN:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(90), m_speed*NNDegreeToY(90)) * dTime );
		break;
	case LEFT:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(180), m_speed*NNDegreeToY(180)) * dTime );
		break;
	case RIGHT:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(0), m_speed*NNDegreeToY(0)) * dTime );
		break;
	case LEFT_UP:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(225), m_speed*NNDegreeToY(225))*dTime );
		break;
	case LEFT_DOWN:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(135), m_speed*NNDegreeToY(135)) * dTime );
		break;
	case RIGHT_UP:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(315), m_speed*NNDegreeToY(315))* dTime );
		break;
	case RIGHT_DOWN:
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(45), m_speed*NNDegreeToY(45)) * dTime );
		break;
	default:
		break;
	}
}