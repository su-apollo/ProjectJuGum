#include "TestScene.h"


CTestScene::CTestScene(void)
{
	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"Something Strange", 75.f );
	m_LogoLabelEnglish->SetPosition( 90.f, 30.f );
	AddChild( m_LogoLabelEnglish );
	
	m_LogoLabelKorean = NNLabel::Create( L"ÁÖ°Ëµé", L"±Ã¼­Ã¼", 50.f );
	m_LogoLabelKorean->SetPosition( 170.f, 105.f );
	AddChild( m_LogoLabelKorean );

	m_PlayMenuLabel = NNLabel::Create( L"Play", L"±Ã¼­Ã¼", 40.f );
	m_PlayMenuLabel->SetPosition( 160.f, 300.f );
	AddChild( m_PlayMenuLabel );

	m_TestMenuLabel = NNLabel::Create( L"test", L"±Ã¼­Ã¼", 40.f );
	m_TestMenuLabel->SetPosition( 160.f, 360.f );
	AddChild( m_TestMenuLabel );

	m_QuitMenuLabel = NNLabel::Create( L"Quit", L"±Ã¼­Ã¼", 40.f );
	m_QuitMenuLabel->SetPosition( 160.f, 420.f );
	AddChild( m_QuitMenuLabel );

	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

	m_KeyOn = 0;
	m_MenuLabel[MENU_PLAY] = m_PlayMenuLabel;
	m_MenuLabel[MENU_TEST] = m_TestMenuLabel;
	m_MenuLabel[MENU_QUIT] = m_QuitMenuLabel;
}


CTestScene::~CTestScene(void)
{
}

void CTestScene::Render()
{
	NNScene::Render();
}

void CTestScene::Update( float dTime )
{
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
			NNSceneDirector::GetInstance()->ChangeScene( CPlaytest::Create() );
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