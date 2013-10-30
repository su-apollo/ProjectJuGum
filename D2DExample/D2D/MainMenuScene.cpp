#include "MainMenuScene.h"


CMainMenuScene::CMainMenuScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();
	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"Something Strange", 100.f );
	m_LogoLabelEnglish->SetColor( 255, 0, 0 );
	m_LogoLabelEnglish->SetPosition( width/2 - 25.f, height/4 - 100.f );
	AddChild( m_LogoLabelEnglish );
	
	m_LogoLabelKorean = NNLabel::Create( L"ÁÖ°Ëµé", L"±Ã¼­Ã¼", 70.f );
	m_LogoLabelKorean->SetPosition( width/2 + 40.f, height/4 );
	AddChild( m_LogoLabelKorean );

	m_MenuLabel[MENU_PLAY] = NNLabel::Create( L"Play", L"±Ã¼­Ã¼", 40.f );
	//m_MenuLabel[MENU_PLAY]->SetCenter(height/2, width/2);
	m_MenuLabel[MENU_PLAY]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[MENU_PLAY] );

	m_MenuLabel[MENU_TEST] = NNLabel::Create( L"Test", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[MENU_TEST]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[MENU_TEST] );

	m_MenuLabel[MENU_QUIT] = NNLabel::Create( L"Quit", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[MENU_QUIT]->SetPosition( width/2 + 60.f, height/2 + 150.f );
	AddChild( m_MenuLabel[MENU_QUIT] );

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
			break;
		case MENU_QUIT:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}
}