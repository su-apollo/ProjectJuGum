#include "MainMenuScene.h"


CMainMenuScene::CMainMenuScene(void)
{
	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"Something Strange", 75.f );
	m_LogoLabelEnglish->SetPosition( 90.f, 30.f );
	AddChild( m_LogoLabelEnglish );
	
	m_LogoLabelKorean = NNLabel::Create( L"ÁÖ°Ëµé", L"±Ã¼­Ã¼", 50.f );
	m_LogoLabelKorean->SetPosition( 170.f, 105.f );
	AddChild( m_LogoLabelKorean );

	m_MenuLabel[MENU_PLAY] = NNLabel::Create( L"Play", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[MENU_PLAY]->SetPosition( 160.f, 300.f );
	AddChild( m_MenuLabel[MENU_PLAY] );

	m_MenuLabel[MENU_TEST] = NNLabel::Create( L"Test", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[MENU_TEST]->SetPosition( 160.f, 362.f );
	AddChild( m_MenuLabel[MENU_TEST] );

	m_MenuLabel[MENU_QUIT] = NNLabel::Create( L"Quit", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[MENU_QUIT]->SetPosition( 160.f, 420.f );
	AddChild( m_MenuLabel[MENU_QUIT] );

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

	m_KeyOn = 0;
}


CMainMenuScene::~CMainMenuScene(void)
{
}

void CMainMenuScene::Render()
{
	NNScene::Render();
}

void CMainMenuScene::Update( float dTime )
{
	// FPS
	swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString(m_FPS);
	
	m_MenuLabel[m_KeyOn]->SetColor( 0, 0, 0 );
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_DOWN )
	{
		--m_KeyOn;
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_DOWN )
	{
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + MENU_LAST) % MENU_LAST;
	m_MenuLabel[m_KeyOn]->SetColor( 255, 0, 0 );

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_DOWN )
	{
		switch (m_KeyOn)
		{
		case MENU_PLAY:
			NNSceneDirector::GetInstance()->ChangeScene( CPlayScene::Create() );
			break;
		case MENU_TEST:
			NNSceneDirector::GetInstance()->ChangeScene( CustomObjectExample::Create() );
			break;
		case MENU_QUIT:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}
}