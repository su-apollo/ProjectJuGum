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

	// ÇÃ·¹ÀÌ ¾À ÀüÃ¼ È­¸é ¹è°æ ÀÌ¹ÌÁö
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition(NNPoint( width/2, height/2));
	m_BackGround->SetImageHeight( height);
	m_BackGround->SetImageWidth( width);
	AddChild(m_BackGround);

	//¸Ê»ı¼º
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_FPSLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;

	// cost
	m_Map->GetPlayer1()->SetCost(10000);
	m_Map->GetPlayer2()->SetCost(0);
	
	m_CostPerSecond = 5.f;
	
	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	m_Player1CostLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_Player1CostLabel );
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	m_Player2CostLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_Player2CostLabel );

	//³×Æ®¿öÅ© ¼³Á¤ ¸Ş´º
	m_MenuLabel[TEST_MODE] = NNLabel::Create( L"TEST", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[TEST_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_MenuLabel[TEST_MODE]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[TEST_MODE] );


	m_MenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[CLIENT_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[CLIENT_MODE]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[CLIENT_MODE] );

	m_MenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[SERVER_MODE]->SetPosition( width/2 + 60.f, height/2 + 160.f );
	AddChild( m_MenuLabel[SERVER_MODE] );

	m_KeyOn = 0;
}

CPlayScene::~CPlayScene(void)
{
	delete GNetHelper;
}

void CPlayScene::Render()
{
	NNScene::Render();
}
void CPlayScene::Update( float dTime )
{
	if(!NetworkSetMenu())
	{
		return;
	}

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


	// ¾À¿¡¼­ Ã³¸®ÇÏ´ø ¸ğµç Ã³¸®¸¦ ¸ŞÀÎ ¸ÊÀ¸·Î ³Ñ±è.
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

	//ip
	char* serverIpAddr = "127.0.0.1";
	//char* serverIpAddr = "10.73.38.244";

	//¸Ş´º
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
			m_Map->SetGameMode(TEST_MODE);
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

			m_Map->GetPlayer1()->SetPosition( 0.f, m_Map->GetBotLine() *0.5f );
			m_Map->GetPlayer2()->SetPosition( 0.f, m_Map->GetTopLine() *0.5f );

			m_Map->SetGameMode(CLIENT_MODE);
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

			m_Map->SetGameMode(SERVER_MODE);
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
