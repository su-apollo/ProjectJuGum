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

#include "NetManager.h"

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
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"맑은 고딕", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_FPSLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;

	// cost
	m_Map->GetPlayer1()->SetCost(10000);
	m_Map->GetPlayer2()->SetCost(0);
	
	m_CostPerSecond = 5.f;
	
	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"맑은 고딕", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	m_Player1CostLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_Player1CostLabel );
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"맑은 고딕", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	m_Player2CostLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_Player2CostLabel );

	//네트워크 설정 메뉴
	m_MenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", L"궁서체", 40.f );
	m_MenuLabel[CLIENT_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_MenuLabel[CLIENT_MODE]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[CLIENT_MODE] );

	m_MenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", L"궁서체", 40.f );
	m_MenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[SERVER_MODE]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[SERVER_MODE] );

	m_KeyOn = 0;
}

CPlayScene::~CPlayScene(void)
{
}

void CPlayScene::Render()
{
	NNScene::Render();
}
void CPlayScene::Update( float dTime )
{
// 	if(!NetworkSetMenu())
// 	{
// 		return;
// 	}

	// FPS
	m_SumTime += dTime;
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString( m_FPSBuffer );


	// cost
	m_Map->GetPlayer1()->SetCost( m_Map->GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	m_Map->GetPlayer2()->SetCost( m_Map->GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"Player1's Cost : %d", (int)(m_Map->GetPlayer1()->GetCost()) );
	m_Player1CostLabel->SetString( m_Player1CostBuffer );
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"Player2's Cost : %d", (int)(m_Map->GetPlayer2()->GetCost()) );
	m_Player2CostLabel->SetString( m_Player2CostBuffer );


	// 씬에서 처리하던 모든 처리를 메인 맵으로 넘김.
	m_Map->Update( dTime );
	if ( m_Map->IsGameEnd() ) EndGame();
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

	//네트워크 메뉴와 소켓 초기화
	char* serverIpAddr = "127.0.0.1";

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
	m_KeyOn = (m_KeyOn + NET_MENU_LAST) % NET_MENU_LAST;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f);


	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		switch (m_KeyOn)
		{
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

			m_Map->GetPlayer1()->SetPosition( 0.f, m_Map->GetBotLine() *0.5f );
			m_Map->GetPlayer2()->SetPosition( 0.f, m_Map->GetTopLine() *0.5f );

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

			m_Map->GetPlayer1()->SetPosition( 0.f, m_Map->GetTopLine() *0.5f );
			m_Map->GetPlayer2()->SetPosition( 0.f, m_Map->GetBotLine() *0.5f );

			break;
		default:
			break;
		}

		m_netsetup = true;
		m_MenuLabel[0]->SetVisible(false);
		m_MenuLabel[1]->SetVisible(false);
		return true;
	}
	return false;
}
