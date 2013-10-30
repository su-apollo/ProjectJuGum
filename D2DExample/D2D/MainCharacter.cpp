#include "Maincharacter.h"
#include "NNInputSystem.h"

CMaincharacter::CMaincharacter(void)
{
	m_Circle = NNCircle::Create(20.f);
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
	UpdateMotion(dTime);
}

void CMaincharacter::UpdateMotion(float dTime)
{
	//입력에 따른 캐릭터의 이동
	if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(225), m_speed*NNDegreeToY(225))*dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(315), m_speed*NNDegreeToY(315))* dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(135), m_speed*NNDegreeToY(135)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(45), m_speed*NNDegreeToY(45)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(180), m_speed*NNDegreeToY(180)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(0), m_speed*NNDegreeToY(0)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(90), m_speed*NNDegreeToY(90)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*NNDegreeToX(270), m_speed*NNDegreeToY(270)) * dTime );
	}
}