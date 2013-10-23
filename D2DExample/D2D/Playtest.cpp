#include "Playtest.h"
#include "NNInputSystem.h"

CPlaytest::CPlaytest(void) : 
	m_BulletIndex(0)
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
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SHIFT ) == KEY_DOWN && m_BulletIndex < 5 )
	{
		m_Bullet[m_BulletIndex] = CBullet::Create();
		AddChild( m_Bullet[m_BulletIndex] );

		m_Bullet[m_BulletIndex]->SetPosition( m_Player->GetPosition() );
		++m_BulletIndex;
	}

	for (int i = 0; i < m_BulletIndex; ++i)
	{
		m_Bullet[i]->Update(dTime);
	}
	
	m_Player->Update(dTime);
}