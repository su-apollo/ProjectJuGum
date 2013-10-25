#include "ReturnScene.h"
#include "NNInputSystem.h"
#include "NNSceneDirector.h"
#include "MainMenuScene.h"


CReturnScene::CReturnScene(void)
{
	m_ReturnLabel = NNLabel::Create( L"Return to Main Menu? ", L"±Ã¼­Ã¼", 75.f );
	m_ReturnLabel->SetPosition( 50.f, 30.f );
	AddChild( m_ReturnLabel );

	m_YesLabel = NNLabel::Create( L"Yes", L"±Ã¼­Ã¼", 60.f );
	m_YesLabel->SetPosition( 250.f, 250.f );
	AddChild( m_YesLabel );

	m_NoLabel = NNLabel::Create( L"No", L"±Ã¼­Ã¼", 60.f );
	m_NoLabel->SetPosition( 500.f, 250.f );
	AddChild( m_NoLabel );

	m_bReturn = false;
	m_NoLabel->SetColor( 255, 0, 0 );
}


CReturnScene::~CReturnScene(void)
{
}

void CReturnScene::Render()
{
	NNScene::Render();
}

void CReturnScene::Update( float dTime )
{
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN )
	{
		m_bReturn = !m_bReturn;
		// printf_s("%d\n", m_bReturn);

		switch (m_bReturn)
		{
		case true:
			// printf_s( " Yes! \n");
			m_NoLabel->SetColor( 0, 0, 0 );
			m_YesLabel->SetColor( 255, 0, 0 );
			break;
		case false:
			// printf_s( " No! \n");
			m_YesLabel->SetColor( 0, 0, 0 );
			m_NoLabel->SetColor( 255, 0, 0 );
			break;
		default:
			break;
		}
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_DOWN )
	{
		switch (m_bReturn)
		{
		case true:
			NNSceneDirector::GetInstance()->ChangeScene( CMainMenuScene::Create() );
			break;
		case false:
			NNSceneDirector::GetInstance()->BackToPrevScene();			
			break;
		default:
			break;
		}
	}
}
