#include "MainMenuScene.h"


CMainMenuScene::CMainMenuScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_Logo = NNSprite::Create( L"Sprite/logo.png" );
	float image_ratio = (float)width * 0.5f / m_Logo->GetImageWidth();
	m_Logo->SetImageWidth(m_Logo->GetImageWidth() * image_ratio);
	m_Logo->SetImageHeight(m_Logo->GetImageHeight() * image_ratio);
	m_Logo->SetPosition( width/2, height/4 );
	AddChild( m_Logo );

	m_MenuLabel[MENU_PLAY] = NNLabel::Create( L"Play", L"±Ã¼­Ã¼", 40.f );
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
			NNSceneDirector::GetInstance()->ChangeScene( new CPlayScene() );
			break;
		case MENU_TEST:
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}