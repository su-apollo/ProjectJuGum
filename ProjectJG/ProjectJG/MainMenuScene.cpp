#include "NNConfig.h"

#include "MainMenuScene.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "NNApplication.h"
#include "PlayScene.h"
#include "NNSprite.h"
#include "NNAudioSystem.h"


CMainMenuScene::CMainMenuScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// BGM
	m_BackgroundSound = NNResourceManager::GetInstance()->LoadSoundFromFile( MAIN_MENU_SCENE_BACKGROUND_SOUND, true );
	NNAudioSystem::GetInstance()->Play( m_BackgroundSound );

	// 배경 이미지
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition( NNPoint(width*0.5f, height*0.5f) );
	m_BackGround->SetImageHeight(height);
	m_BackGround->SetImageWidth(width);
	AddChild(m_BackGround);

	// 로고 ("JuGums")
	m_Logo = NNSprite::Create( MAIN_MENU_SCENE_LOGO );
	float image_ratio = (float)width * 0.5f / m_Logo->GetImageWidth();
	m_Logo->SetImageWidth(m_Logo->GetImageWidth() * image_ratio);
	m_Logo->SetImageHeight(m_Logo->GetImageHeight() * image_ratio);
	m_Logo->SetPosition( width*0.5f, height*0.25f );
	AddChild( m_Logo );


	// 메뉴 라벨 생성 및 배치
	m_MenuLabel[MENU_TEST] = NNLabel::Create( L"Test", GAME_FONT, 40.f );
	m_MenuLabel[MENU_TEST]->SetPosition( width*0.5f + 60.f, height*0.5f - 60.f );
	AddChild( m_MenuLabel[MENU_TEST] );

	m_MenuLabel[MENU_SERVER] = NNLabel::Create( L"Server", GAME_FONT, 40.f );
	m_MenuLabel[MENU_SERVER]->SetPosition( width*0.5f + 60.f, height*0.5f + 20.f );
	AddChild( m_MenuLabel[MENU_SERVER] );

	m_MenuLabel[MENU_CLIENT] = NNLabel::Create( L"Client", GAME_FONT, 40.f );
	m_MenuLabel[MENU_CLIENT]->SetPosition( width*0.5f + 60.f, height*0.5f + 100.f );
	AddChild( m_MenuLabel[MENU_CLIENT] );

	m_MenuLabel[MENU_QUIT] = NNLabel::Create( L"Quit", GAME_FONT, 40.f );
	m_MenuLabel[MENU_QUIT]->SetPosition( width*0.5f + 60.f, height*0.5f + 180.f );
	AddChild( m_MenuLabel[MENU_QUIT] );

	m_KeyOn = 0;			// 현재 가리키고 있는 메뉴 위치

	m_LoadingLabel = NNLabel::Create(L"Loading...", GAME_FONT, 50.f);
	m_LoadingLabel->SetPosition( m_MenuLabel[MENU_TEST]->GetPosition() );
	m_LoadingLabel->SetVisible(false);
	AddChild( m_LoadingLabel );

	m_bChangeScene = false;
}


CMainMenuScene::~CMainMenuScene(void)
{
	NNAudioSystem::GetInstance()->Stop( m_BackgroundSound );
}

void CMainMenuScene::Render()
{
	NNScene::Render();
}

void CMainMenuScene::Update( float dTime )
{
	if (m_bChangeScene)
	{
		NNSceneDirector::GetInstance()->ChangeScene( new CPlayScene(m_GameMode) );
		return;
	}
	
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 255.f, 255.f );
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT)
	{
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + MENU_NUM) % MENU_NUM;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f );

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		if (m_KeyOn != MENU_QUIT)
		{
			for (int i = 0; i < MENU_NUM; i++)
			{
				m_MenuLabel[i]->SetVisible(false);
			}
			m_LoadingLabel->SetVisible(true);
			m_bChangeScene = true;
		}
		switch (m_KeyOn)
		{
		case MENU_TEST:
			m_GameMode = TEST_MODE;
			break;
		case MENU_CLIENT:
			m_GameMode = CLIENT_MODE;
			break;
		case MENU_SERVER:
			m_GameMode = SERVER_MODE;
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}