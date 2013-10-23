#include "Player.h"
#include "NNInputSystem.h"

CPlayer::CPlayer(void)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 100.f);
	AddChild( m_Circle );

	m_speed = 50.f;
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Render()
{
	NNObject::Render();
}

void CPlayer::Update( float dTime )
{
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(-m_speed,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(m_speed,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(0.f,-m_speed) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED )
	{
		SetPosition( GetPosition() + NNPoint(0.f,m_speed) * dTime );
	}
}