#include "NNConfig.h"

#include "NNLabel.h"
#include "NNSceneDirector.h"
#include "NNApplication.h"
#include "NNSprite.h"
#include "NNInputSystem.h"
#include "NNNetworkSystem.h"
#include "PacketType.h"

#include "PlayScene.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "MainMenuScene.h"
#include "MainMap.h"
#include "Frame.h"
#include "Camera.h"
#include "UImanager.h"
#include "PacketHandler.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"

CPlayScene::CPlayScene( ENetworkMode GameMode, char* serverIP ) : m_netsetup(false), m_DoCount(true), m_CountNum(0.f)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// 게임 메인 맵
	m_MainMap = new CMainMap(GameMode);
	m_MainMap->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	AddChild(m_MainMap);

	// 카메라 프레임
	m_Frame = new CFrame();
	m_Frame->SetPosition( width*0.5f, height*0.5f );
	m_Frame->SetSize( FRAME_WIDTH, FRAME_HEIGHT );
	AddChild( m_Frame );

	//카운트다운을 위한 라벨
	m_CountNumLabel_3 = NNLabel::Create(L"3", L"궁서체", 40.f);
	m_CountNumLabel_3->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_3->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_3->SetVisible(false);
	AddChild( m_CountNumLabel_3 );

	m_CountNumLabel_2 = NNLabel::Create(L"2", L"궁서체", 40.f);
	m_CountNumLabel_2->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_2->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_2->SetVisible(false);
	AddChild( m_CountNumLabel_2 );

	m_CountNumLabel_1 = NNLabel::Create(L"1", L"궁서체", 40.f);
	m_CountNumLabel_1->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_1->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_1->SetVisible(false);
	AddChild( m_CountNumLabel_1 );

	NetworkSetMenu(GameMode, serverIP);

	m_BackgroundSound = NNResourceManager::GetInstance()->LoadSoundFromFile( GAME_BACKGROUND_SOUND, true );
	NNAudioSystem::GetInstance()->Play( m_BackgroundSound );
}

CPlayScene::~CPlayScene(void)
{
	NNAudioSystem::GetInstance()->Stop( m_BackgroundSound );
}

void CPlayScene::Render()
{
	NNScene::Render();
	UImanager::GetInstance()->Render();
}

void CPlayScene::Update( float dTime )
{

	//3초의 카운트다운 후 게임 시작
// 	if (m_DoCount)
// 	{
// 		//3초의 카운트 다운
// 		CountDown(dTime);
// 		return;
// 	}
	
	
	// camera move. 플레이어가 프레임 경계까지 가면 카메라가 따라서 움직인다.
	CameraMove( m_MainMap->GetPlayer1(), dTime );

	// UI update
	UImanager::GetInstance()->Update( dTime, m_MainMap->GetPlayer1(), m_MainMap->GetPlayer2() );

	// 모든 게임 플레이 관련 처리는 메인 맵에서 한다.
	m_MainMap->Update( dTime, m_Frame );

	switch (m_MainMap->GetGameResult())
	{
	case GAME_RESULT_DRAW:
		MessageBox(NULL, L"Draw!", L"Gameover", MB_OK) ;
		break;
	case GAME_RESULT_WIN:
		MessageBox(NULL, L"You Win!", L"Gameover", MB_OK) ;
		break;
	case GAME_RESULT_LOSE:
		MessageBox(NULL, L"You Lose!", L"Gameover", MB_OK) ;
		break;
	default:
		break;
	}
	
	if ( m_MainMap->GetGameResult() )
		EndGame();
}

void CPlayScene::EndGame()
{
	//동기화를 위한 3초간의 슬립
	Sleep(3000);
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
	return;
}

void CPlayScene::CountDown(float dTime)
{
	m_CountNum += dTime;

	if (m_CountNum <= 1.f)
	{
		m_CountNumLabel_3->SetVisible(true);
	}
	
	if (1.f < m_CountNum && m_CountNum <= 2.f)
	{
		m_CountNumLabel_3->SetVisible(false);
		m_CountNumLabel_2->SetVisible(true);
	}

	if (2.f < m_CountNum && m_CountNum <= 3.f)
	{
		m_CountNumLabel_2->SetVisible(false);
		m_CountNumLabel_1->SetVisible(true);
	}

	if( m_CountNum > 3.f )
	{
		m_CountNumLabel_1->SetVisible(false);
		m_DoCount = false;
	}
}

void CPlayScene::NetworkSetMenu( ENetworkMode GameMode, char* serverIP )
{
	//ip
	/*char* serverIpAddr = "127.0.0.1";*/
	char* serverIpAddr = serverIP;

	switch (GameMode)
	{
	case TEST_MODE:
		m_MainMap->SetGameMode(TEST_MODE);
		break;

	case CLIENT_MODE:

		m_MainMap->SetGameMode(CLIENT_MODE);

		NNNetworkSystem::GetInstance()->Init();
		NNNetworkSystem::GetInstance()->Connect(serverIpAddr, SERVER_PORT_NUM);
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer1()->GetPacketHandler());
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer2()->GetPacketHandler());

		//캐릭터를 위치에 배치
		m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );
		m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );


		break;

	case SERVER_MODE:

		m_MainMap->SetGameMode(SERVER_MODE);

		NNNetworkSystem::GetInstance()->Init();
		NNNetworkSystem::GetInstance()->Listen(SERVER_PORT_NUM);
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer1()->GetPacketHandler());
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer2()->GetPacketHandler());

		//연결 후 캐릭터를 위치에 배치
		m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );
		m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );


		break;
	default:
		break;
	}

}


void CPlayScene::CameraMove( CMaincharacter* Player, float dTime )
{
	float leftline = m_Frame->GetLeftLine();
	float rightline = m_Frame->GetRightLine();
	float botline = m_Frame->GetBotLine();
	float topline = m_Frame->GetTopLine();

	CCamera* camera = m_MainMap->GetCamera();

	if (Player->GetPositionX() - camera->GetPositionX() < leftline)
	{
		camera->SetPosition( Player->GetPositionX() - leftline , camera->GetPositionY() );
	}
	if (Player->GetPositionX() - camera->GetPositionX() > rightline)
	{
		camera->SetPosition( Player->GetPositionX() - rightline, camera->GetPositionY() );
	}
	if (Player->GetPositionY() - camera->GetPositionY() > botline)
	{
		camera->SetPosition( camera->GetPositionX(), Player->GetPositionY() - botline );
	}
	if (Player->GetPositionY() - camera->GetPositionY() < topline)
	{
		camera->SetPosition( camera->GetPositionX(), Player->GetPositionY() - topline );
	}
}


