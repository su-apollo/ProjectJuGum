#include "PlayScene.h"

CPlayScene::CPlayScene(void) : 
	m_BulletIndex(0)
{
	m_Player = CMaincharacter::Create();
	AddChild( m_Player );

	m_Player->SetPosition(NNPoint(500.f, 500.f));

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

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
	// FPS
	swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString(m_FPS);
	// ÀÌ°É·Î ÄÜ¼ÖÃ¢¿¡¼­µµ º¼ ¼ö ÀÖ¾î¿ä ÆÀÀå´Ô
	printf_s("FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );

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