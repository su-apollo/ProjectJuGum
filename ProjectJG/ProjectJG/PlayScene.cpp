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

CPlayScene::CPlayScene( ENetworkMode GameMode, char* serverIP ) : m_netsetup(false)
{
	m_GameMode = GameMode;

	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// 게임 메인 맵
	m_MainMap = new CMainMap(GameMode);
	m_MainMap->SetPosition( width *0.5f, height *0.5f );
	AddChild(m_MainMap);

	// 카메라 프레임
	m_Frame = new CFrame();
	m_Frame->SetPosition( m_MainMap->GetPosition() );
	m_Frame->SetSize( FRAME_WIDTH, FRAME_HEIGHT );
	AddChild( m_Frame );

	//게임결과표시와 함께 나오는 메뉴
	m_ReplayLabel = NNLabel::Create(L"Replay", L"궁서체", 40.f);
	m_ReplayLabel->SetColor(255.f, 255.f, 255.f);
	m_ReplayLabel->SetPosition(width*0.5f, height*0.5f);
	m_ReplayLabel->SetVisible(false);
	AddChild(m_ReplayLabel);

	m_ExitLabel = NNLabel::Create(L"Exit", L"궁서체", 40.f);
	m_ExitLabel->SetColor(255.f, 255.f, 255.f);
	m_ExitLabel->SetPosition(width*0.5f, height*0.5f);
	m_ExitLabel->SetVisible(false);
	AddChild(m_ExitLabel);

	//게임결과표시를 위한 스프라이트 로드
	m_SpriteRaymuWin = NNSprite::Create( L"Sprite/charR_win.png" );
	m_SpriteRaymuLose = NNSprite::Create( L"Sprite/charR_lose.png" );
	m_SpriteMarisaWin = NNSprite::Create( L"Sprite/charB_win.png" );
	m_SpriteMarisaLose = NNSprite::Create( L"Sprite/charB_lose.png" );

	m_SpriteRaymuWin->SetPosition( width *0.25f, height *0.5f );
	m_SpriteRaymuLose->SetPosition( width *0.25f, height *0.5f );
	m_SpriteMarisaWin->SetPosition( width *0.75f, height *0.5f );
	m_SpriteMarisaLose->SetPosition( width *0.75f, height *0.5f );

	m_SpriteMarisaLose->SetVisible(false);
	m_SpriteMarisaWin->SetVisible(false);
	m_SpriteRaymuLose->SetVisible(false);
	m_SpriteRaymuWin->SetVisible(false);

	AddChild(m_SpriteRaymuLose);
	AddChild(m_SpriteRaymuWin);
	AddChild(m_SpriteMarisaLose);
	AddChild(m_SpriteMarisaWin);

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
		m_SpriteMarisaLose->SetVisible(true);
		m_SpriteRaymuLose->SetVisible(true);
		if (NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE)
			EndGame();
		break;
	case GAME_RESULT_WIN:
		if (m_GameMode == CLIENT_MODE)
		{
			m_SpriteRaymuLose->SetVisible(true);
			m_SpriteMarisaWin->SetVisible(true);
		}
		else
		{
			m_SpriteRaymuWin->SetVisible(true);
			m_SpriteMarisaLose->SetVisible(true);
		}
		if (NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE)
			EndGame();
		break;
	case GAME_RESULT_LOSE:
		if (m_GameMode == CLIENT_MODE)
		{
			m_SpriteRaymuWin->SetVisible(true);
			m_SpriteMarisaLose->SetVisible(true);
		}
		else
		{
			m_SpriteRaymuLose->SetVisible(true);
			m_SpriteMarisaWin->SetVisible(true);
		}
		if (NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE)
			EndGame();
		break;
	default:
		break;
	}
}

void CPlayScene::EndGame()
{
	if (m_GameMode == TEST_MODE)
	{
		NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
	}
	else
	{
		PostQuitMessage(0);
		//SendMessage(NNApplication::GetInstance()->GetHWND(),WM_DESTROY,NULL,NULL);
	}
	return;
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

		NNNetworkSystem::GetInstance()->Connect(serverIpAddr, SERVER_PORT_NUM);
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer1()->GetPacketHandler());
		NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_STATUS, m_MainMap->GetPlayer2()->GetPacketHandler());

		//캐릭터를 위치에 배치
		m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );
		m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );


		break;

	case SERVER_MODE:

		m_MainMap->SetGameMode(SERVER_MODE);

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


