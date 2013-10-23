#include "TestScene.h"


CTestScene::CTestScene(void)
{

	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"Something Strange", 75.f );
	m_LogoLabelEnglish->SetColor( 255, 0, 0 );
	m_LogoLabelEnglish->SetPosition( 90.f, 30.f );
	AddChild( m_LogoLabelEnglish );

	m_LogoLabelKorean = NNLabel::Create( L"주검들", L"궁서체", 50.f );
	m_LogoLabelKorean->SetPosition( 170.f, 105.f );
	AddChild( m_LogoLabelKorean );

	m_PlayMenuLabel = NNLabel::Create( L"Play", L"궁서체", 40.f );
	m_PlayMenuLabel->SetPosition( 160.f, 300.f );
	AddChild( m_PlayMenuLabel );

	m_TestMenuLabel = NNLabel::Create( L"test", L"궁서체", 40.f );
	m_TestMenuLabel->SetPosition( 160.f, 360.f );
	AddChild( m_TestMenuLabel );

	m_QuitMenuLabel = NNLabel::Create( L"Quit", L"궁서체", 40.f );
	m_QuitMenuLabel->SetPosition( 160.f, 420.f );
	AddChild( m_QuitMenuLabel );

	m_KeyOn = 0;
	m_MenuLabel[0] = m_PlayMenuLabel;
	m_MenuLabel[1] = m_TestMenuLabel;
	m_MenuLabel[2] = m_QuitMenuLabel;
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
	m_MenuLabel[m_KeyOn]->SetColor( 0, 0, 0 );
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_DOWN )
	{
		m_KeyOn = --m_KeyOn % 3;
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_DOWN )
	{
		m_KeyOn = ++m_KeyOn % 3;
	}

	printf_s("point : %d\n", m_KeyOn);				// 콘솔 창 출력 예시.
	m_MenuLabel[m_KeyOn]->SetColor( 255, 0, 0 );
}