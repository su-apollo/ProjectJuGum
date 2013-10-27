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
	if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(225), m_speed*NNAngleToY(225))*dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(315), m_speed*NNAngleToY(315)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(135), m_speed*NNAngleToY(135)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(45), m_speed*NNAngleToY(45)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(180), m_speed*NNAngleToY(180)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(0), m_speed*NNAngleToY(0)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(90), m_speed*NNAngleToY(90)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNAngleToX(270), m_speed*NNAngleToY(270)) * dTime );
	}
}