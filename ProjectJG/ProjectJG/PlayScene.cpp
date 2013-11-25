#include "NNConfig.h"

#include "NNLabel.h"
#include "NNSceneDirector.h"
#include "NNApplication.h"
#include "NNSprite.h"

#include "PlayScene.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "MainMenuScene.h"
#include "MainMap.h"
#include "UImanager.h"

#include "NetManager.h"

#include "Frame.h"
#include "Camera.h"

CPlayScene::CPlayScene(void) : m_netsetup(false)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// 플레이 씬 전체 화면 배경 이미지
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition(NNPoint( width/2, height/2));
	m_BackGround->SetImageHeight( height);
	m_BackGround->SetImageWidth( width);
	AddChild(m_BackGround);

	//맵생성
	m_MainMap = new CMainMap();
	m_MainMap->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_MainMap);

	// cost
	m_CostPerSecond = 5.f;

	//네트워크 설정 메뉴
	m_MenuLabel[TEST_MODE] = NNLabel::Create( L"TEST", L"궁서체", 40.f );
	m_MenuLabel[TEST_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_MenuLabel[TEST_MODE]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[TEST_MODE] );


	m_MenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", L"궁서체", 40.f );
	m_MenuLabel[CLIENT_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[CLIENT_MODE]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[CLIENT_MODE] );

	m_MenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", L"궁서체", 40.f );
	m_MenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[SERVER_MODE]->SetPosition( width/2 + 60.f, height/2 + 160.f );
	AddChild( m_MenuLabel[SERVER_MODE] );

	m_KeyOn = 0;


	m_Frame = new CFrame();
	m_Frame->SetPosition( width*0.5f, height*0.5f );
	m_Frame->SetSize( FRAME_WIDTH, FRAME_HEIGHT );
	AddChild( m_Frame );
}

CPlayScene::~CPlayScene(void)
{
	delete GNetHelper;
}

void CPlayScene::Render()
{
	NNScene::Render();
	UImanager::GetInstance()->Render();
}
void CPlayScene::Update( float dTime )
{
	if(!NetworkSetMenu())
	{
		return;
	}
	
	// cost
	m_MainMap->GetPlayer1()->SetCost( m_MainMap->GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	m_MainMap->GetPlayer2()->SetCost( m_MainMap->GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	// camera move
	CameraMove( m_MainMap->GetPlayer1(), dTime );

	// UI update
	UImanager::GetInstance()->Update( dTime, m_MainMap->GetPlayer1(), m_MainMap->GetPlayer2() );

	// 씬에서 처리하던 모든 처리를 메인 맵으로 넘김.
	m_MainMap->Update( dTime, m_Frame );
	if ( m_MainMap->IsGameEnd() ) EndGame();
}

bool CPlayScene::CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B) 
{
	if((radius_A + radius_B) > point_A.GetDistance(point_B))
	{
		return true;
	}
	return false;
}

void CPlayScene::EndGame()
{
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
	return;
}

bool CPlayScene::NetworkSetMenu()
{
	if (m_netsetup)
	{
		return true;
	}

	//ip
	char* serverIpAddr = "127.0.0.1";
	//char* serverIpAddr = "10.73.38.244";

	//메뉴
	m_MenuLabel[m_KeyOn]->SetColor( 0.f, 0.f, 0.f);	
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT )
	{
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		++m_KeyOn;
	}
	m_KeyOn %= NET_MENU_LAST;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f);


	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		switch (m_KeyOn)
		{
		case TEST_MODE:
			m_MainMap->SetGameMode(TEST_MODE);
			break;

		case CLIENT_MODE:
			GNetHelper = new NetHelper(false, serverIpAddr) ;

			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return false;
			}

			if ( !GNetHelper->DoHandShake() )
			{
				return false;
			}

			m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );
			m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );

			m_MainMap->SetGameMode(CLIENT_MODE);
			break;

		case SERVER_MODE:
			GNetHelper = new NetHelper(true, serverIpAddr) ;

			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return false;
			}

			if ( !GNetHelper->DoHandShake() )
			{
				return false;
			}

			m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );
			m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );

			m_MainMap->SetGameMode(SERVER_MODE);
			break;
		default:
			break;
		}

		m_netsetup = true;
		m_MenuLabel[0]->SetVisible(false);
		m_MenuLabel[1]->SetVisible(false);
		m_MenuLabel[2]->SetVisible(false);

		return true;
	}
	return false;
}


void CPlayScene::CameraMove( CMaincharacter* Player, float dTime )
{
	float leftline = m_Frame->GetLeftLine();
	float rightline = m_Frame->GetRightLine();
	float botline = m_Frame->GetBotLine();
	float topline = m_Frame->GetTopLine();

	CCamera* camera = m_MainMap->GetCamera();

	float dX = 0;
	float dY = 0;

	printf_s("frame : %.3f, %.3f, %.3f, %.3f\n", leftline, topline, rightline, botline);
	printf_s("player : %.3f, %.3f\ncamera : %.3f, %.3f\n", Player->GetPositionX(), Player->GetPositionY(), camera->GetPositionX(), camera->GetPositionY())

	if (Player->GetPositionX() - camera->GetPositionX() < leftline)
	{
		camera->SetPosition( camera->GetPosition() + NNPoint(Player->GetPositionX() - camera->GetPositionX() - leftline, 0) );
	}
	if (Player->GetPositionX() - camera->GetPositionX() > rightline)
	{
		camera->SetPosition( camera->GetPosition() + NNPoint(Player->GetPositionX() - camera->GetPositionX() - rightline, 0) );
	}
	if (Player->GetPositionY() - camera->GetPositionY() > botline)
	{
		camera->SetPosition( camera->GetPosition() + NNPoint(0, Player->GetPositionY() - camera->GetPositionY() - botline) );
	}
	if (Player->GetPositionY() - camera->GetPositionY() < topline)
	{
		camera->SetPosition( camera->GetPosition() + NNPoint(0, Player->GetPositionY() - camera->GetPositionY() - topline) );
	}
}