#include "TestScene.h"


CTestScene::CTestScene(void)
{

	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"±Ã¼­Ã¼", 75.f );
	m_LogoLabelEnglish->SetPosition( 90.f, 30.f );
	AddChild( m_LogoLabelEnglish );

	m_LogoLabelKorean = NNLabel::Create( L"ÁÖ°Ëµé", L"±Ã¼­Ã¼", 50.f );
	m_LogoLabelKorean->SetPosition( 170.f, 105.f );
	AddChild( m_LogoLabelKorean );

	m_PlayMenuLabel = NNLabel::Create( L"Play", L"±Ã¼­Ã¼", 40.f );
	m_PlayMenuLabel->SetPosition( 160.f, 320.f );
	AddChild( m_PlayMenuLabel );

	m_QuitMenuLabel = NNLabel::Create( L"Quit", L"±Ã¼­Ã¼", 40.f );
	m_QuitMenuLabel->SetPosition( 160.f, 420.f );
	AddChild( m_QuitMenuLabel );
}


CTestScene::~CTestScene(void)
{
}

void CTestScene::Render()
{
	NNObject::Render();
}

void CTestScene::Update( float dTime )
{
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN )
	{
		m_PlayMenuLabel->SetColor( 255, 0, 0 );
		m_QuitMenuLabel->SetColor( 0, 0, 0);
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN )
	{
		m_PlayMenuLabel->SetColor( 0, 0, 0 );
		m_QuitMenuLabel->SetColor( 255, 0, 0);
	}
}