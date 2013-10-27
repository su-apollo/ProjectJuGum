#include "PlayScene.h"

CPlayScene::CPlayScene(void) : 
	m_BulletIndex1(0), m_BulletIndex2(0)
{
	m_Player1 = CMaincharacter::Create();
	m_Player2 = CMaincharacter::Create();

	m_Player2->SetKeyUp('W');
	m_Player2->SetKeyDown('S');
	m_Player2->SetKeyLeft('A');
	m_Player2->SetKeyRight('D');

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	m_Player1->SetPosition(NNPoint(600.f, 700.f));
	m_Player2->SetPosition(NNPoint(600.f, 100.f));

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

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SPACE ) == KEY_DOWN && m_BulletIndex1 < MAX_BULLET_NUM )
	{
		m_Bullet1[m_BulletIndex1] = CBullet::Create();
		AddChild( m_Bullet1[m_BulletIndex1] );

		m_Bullet1[m_BulletIndex1]->SetPosition( m_Player1->GetPosition() );
		++m_BulletIndex1;
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SHIFT ) == KEY_DOWN && m_BulletIndex2 < MAX_BULLET_NUM )
	{
		m_Bullet2[m_BulletIndex2] = CBullet::Create();
		m_Bullet2[m_BulletIndex2]->SetDirection(90);
		AddChild( m_Bullet2[m_BulletIndex2] );

		m_Bullet2[m_BulletIndex2]->SetPosition( m_Player2->GetPosition() );
		++m_BulletIndex2;
	}

	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		m_Bullet1[i]->Update(dTime);
	}

	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		m_Bullet2[i]->Update(dTime);
	}
	
	m_Player1->Update(dTime);
	m_Player2->Update(dTime);
}