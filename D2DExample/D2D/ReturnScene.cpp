#include "ReturnScene.h"
#include "MainMenuScene.h"
#include "NNSceneDirector.h"
#include "NNInputSystem.h"
#include "NNLabel.h"
#include "NNApplication.h"

CReturnScene::CReturnScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_ReturnLabel = NNLabel::Create( L"Return to Main Menu? ", L"±Ã¼­Ã¼", 75.f );
	m_ReturnLabel->SetPosition( width/2 - 220.f, height/4 );
	AddChild( m_ReturnLabel );

	m_YesLabel = NNLabel::Create( L"Yes", L"±Ã¼­Ã¼", 60.f );
	m_YesLabel->SetPosition( width/2 - 50.f, height/2 );
	AddChild( m_YesLabel );

	m_NoLabel = NNLabel::Create( L"No", L"±Ã¼­Ã¼", 60.f );
	m_NoLabel->SetPosition( width/2 + 200.f, height/2 );
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

		if (m_bReturn)
		{
			m_NoLabel->SetColor( 0, 0, 0 );
			m_YesLabel->SetColor( 255, 0, 0 );
		} 
		else
		{
			m_YesLabel->SetColor( 0, 0, 0 );
			m_NoLabel->SetColor( 255, 0, 0 );
		}
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_DOWN )
	{
		if (m_bReturn)
		{
			NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
		} 
		else
		{
			NNSceneDirector::GetInstance()->BackToPrevScene();
		}
	}
}
