#include "Maincharacter.h"
#include "NNInputSystem.h"

CMaincharacter::CMaincharacter(void)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );

	m_speed = 500.f;
	m_keyup = VK_UP;
	m_keydown = VK_DOWN;
	m_keyright = VK_RIGHT;
	m_keyleft = VK_LEFT;

	m_AreaLeft = -10000.f;
	m_AreaRight = 10000.f;
	m_AreaTop = -10000.f;
	m_AreaBottom = 10000.f;
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
	if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		if ( GetPosition().GetX() + NNAngleToX(225)*dTime >= m_AreaLeft)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(225), 0.f)*dTime );
		}
		if ( GetPosition().GetY() + NNAngleToY(225)*dTime >= m_AreaTop)
		{
			SetPosition( GetPosition() + NNPoint(0.f, m_speed*NNAngleToY(225))*dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		if (GetPosition().GetX() <= m_AreaRight)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(315), 0.f)* dTime );
		}
		if (GetPosition().GetY() >= m_AreaTop)
		{
			SetPosition( GetPosition() + NNPoint(0.f, m_speed*NNAngleToY(315))* dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		if(GetPosition().GetX() >= m_AreaLeft )
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(135), 0.f) * dTime );
		}
		if(GetPosition().GetY() <= m_AreaBottom)
		{
			SetPosition( GetPosition() + NNPoint(0.f, m_speed*NNAngleToY(135)) * dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		if (GetPosition().GetX() <= m_AreaRight )
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(45), 0.f) * dTime );
		}	
		if (GetPosition().GetY() <= m_AreaBottom)
		{
			SetPosition( GetPosition() + NNPoint(0.f, m_speed*NNAngleToY(45)) * dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		if (GetPosition().GetX() >= m_AreaLeft)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(180), m_speed*NNAngleToY(180)) * dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		if (GetPosition().GetX() <= m_AreaRight)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(0), m_speed*NNAngleToY(0)) * dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED )
	{
		if (GetPosition().GetY() <= m_AreaBottom)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(90), m_speed*NNAngleToY(90)) * dTime );
		}
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED )
	{
		if (GetPosition().GetY() >= m_AreaTop)
		{
			SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(270), m_speed*NNAngleToY(270)) * dTime );
		}
	}
}

void CMaincharacter::SetMoveArea(float left, float right, float top, float bottom)
{
	m_AreaLeft = left;
	m_AreaRight = right;
	m_AreaTop = top;
	m_AreaBottom = bottom;
}