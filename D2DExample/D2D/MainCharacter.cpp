#include "Maincharacter.h"
#include "NNInputSystem.h"

CMaincharacter::CMaincharacter(void)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 100.f);
	AddChild( m_Circle );

	m_speed = 500.f;
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
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*225/180),m_speed*(float)sin(NN_PI*225/180) ) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*315/180),m_speed*(float)sin(NN_PI*315/180) ) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*135/180),m_speed*(float)sin(NN_PI*135/180) ) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*45/180),m_speed*(float)sin(NN_PI*45/180) ) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*180/180),m_speed*(float)sin(NN_PI*180/180)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*0/180),m_speed*(float)sin(NN_PI*0/180)) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*90/180),m_speed*(float)sin(NN_PI*90/180) ) * dTime );
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed*(float)cos(NN_PI*270/180),m_speed*(float)sin(NN_PI*270/180) ) * dTime );
	}
}