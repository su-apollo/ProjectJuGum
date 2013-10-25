#include "PlayScene.h"
#include "NNInputSystem.h"

CPlayScene::CPlayScene(void) : 
	m_BulletIndex(0)
{
	m_Player = CMaincharacter::Create();
	AddChild( m_Player );

	m_Player->SetPosition(NNPoint(500.f, 500.f));
}

CPlayScene::~CPlayScene(void)
{
}

void CPlayScene::Render()
{
	NNScene::Render();
}
void CPlayScene::Update( float dTime )
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