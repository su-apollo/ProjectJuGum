#include "Playtest.h"
#include "NNInputSystem.h"

CPlaytest::CPlaytest(void)
{
	m_Player = CPlayer::Create();
	AddChild( m_Player );

	m_Player->SetPosition(NNPoint(500.f, 500.f));
}

CPlaytest::~CPlaytest(void)
{
}

void CPlaytest::Render()
{
	NNScene::Render();
}
void CPlaytest::Update( float dTime )
{
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SHIFT ) == KEY_DOWN )
	{
		m_Bullet = CBullet::Create();
		AddChild( m_Bullet );

		m_Bullet->SetPosition( m_Player->GetPosition() );
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		m_Player->SetPosition( m_Player->GetPosition() + NNPoint(-50.f,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		m_Player->SetPosition( m_Player->GetPosition() + NNPoint(50.f,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED )
	{
		m_Player->SetPosition( m_Player->GetPosition() + NNPoint(0.f,-50.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED )
	{
		m_Player->SetPosition( m_Player->GetPosition() + NNPoint(0.f,50.f) * dTime );
	}
}