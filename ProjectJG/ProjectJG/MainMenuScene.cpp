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

	//effectsound
	m_OkSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_OK, false );
	m_CancelSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_CANCEL, false );
	m_SelectSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_SELECT, false );

	// 배경 이미지
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition( width*0.5f, height*0.5f );
	m_BackGround->SetImageHeight(height);
	m_BackGround->SetImageWidth(width);
	AddChild(m_BackGround);

	// 로고 ("JuGums")
	m_Logo = NNSprite::Create( MAIN_MENU_SCENE_LOGO );
	float image_ratio = (float)width * 0.5f / m_Logo->GetImageWidth();
// 	m_Logo->SetImageWidth(m_Logo->GetImageWidth() * image_ratio);
// 	m_Logo->SetImageHeight(m_Logo->GetImageHeight() * image_ratio);
	m_Logo->SetScale(1.3f, 1.3f);
	m_Logo->SetPosition( 170.f, 300.f );
	AddChild( m_Logo );


	// 메뉴 라벨 생성
	m_MenuLabel[MENU_TEST] = NNLabel::Create( L"Test", GAME_FONT, LABEL_FONT_SIZE );
	AddChild( m_MenuLabel[MENU_TEST] );

	m_MenuLabel[MENU_SERVER] = NNLabel::Create( L"Server", GAME_FONT, LABEL_FONT_SIZE );
	AddChild( m_MenuLabel[MENU_SERVER] );

	m_MenuLabel[MENU_CLIENT] = NNLabel::Create( L"Client", GAME_FONT, LABEL_FONT_SIZE );
	AddChild( m_MenuLabel[MENU_CLIENT] );

	m_MenuLabel[MENU_QUIT] = NNLabel::Create( L"Quit", GAME_FONT, LABEL_FONT_SIZE );
	AddChild( m_MenuLabel[MENU_QUIT] );

	// 메뉴 라벨 초기 배치
	m_MenuLabel[0]->SetPosition( width*0.5f + 60.f, height*0.5f - 60.f );
	for (int i = 1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i-1]->GetPosition() + NNPoint(0.f, LABEL_HEIGHT) );
	}


	m_KeyOn = 0;			// 현재 가리키고 있는 메뉴 위치

	// 설명 라벨
	swprintf(m_InstructionBuffer, _countof(m_InstructionBuffer), L"%s\n%s", L"Press", L"Z to select");
	m_InstructionLabel = NNLabel::Create(m_InstructionBuffer, GAME_FONT, LABEL_FONT_SIZE * 0.5f);
	m_InstructionLabel->SetPosition( width*0.5f - 150.f, height*0.5f );
	AddChild(m_InstructionLabel);

	// 네트워크 메뉴 라벨 초기화
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		swprintf(m_NetMenuBuffer[i], _countof(m_NetMenuBuffer[i]), L"");
		m_NetMenuLabel[i] = NNLabel::Create(m_NetMenuBuffer[i], GAME_FONT, LABEL_FONT_SIZE * 0.5f);
		m_NetMenuLabel[i]->SetVisible(false);
		AddChild(m_NetMenuLabel[i]);
	}

	m_bChangeScene = false;
	m_GameMode = MODE_NONE;
	strcpy_s(m_serverIP, _countof(m_serverIP), "");
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
		NNSceneDirector::GetInstance()->ChangeScene( new CPlayScene(m_GameMode, m_serverIP) );
		return;
	}

	// 현재 선택된 게임 모드에 따라 업데이트를 달리 함.
	switch (m_GameMode)
	{
	case TEST_MODE:
		break;
	case SERVER_MODE:
		if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE ) 
		{
			NNAudioSystem::GetInstance()->Play( m_OkSound );
			ChangeScene();
		}
		if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_TWO ) 
		{
			NNAudioSystem::GetInstance()->Play( m_CancelSound );
			CancelModeSelection();
		}
		break;
	case CLIENT_MODE:
		if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE ) 
		{
			NNAudioSystem::GetInstance()->Play( m_OkSound );
			ChangeScene();
		}
		if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_TWO ) 
		{
			NNAudioSystem::GetInstance()->Play( m_CancelSound );
			CancelModeSelection();
		}
		GetIPInput();
		break;
	case MODE_NONE:
		// 아직 게임 모드가 설정되지 않았을 경우, 키보드(화살표) 입력에 따른 메뉴라벨 처리.
		SetUpGameMode();
		break;
	default:
		break;
	}

}

void CMainMenuScene::SetUpGameMode()
{
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 255.f, 255.f );
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT)
	{
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + MENU_NUM) % MENU_NUM;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f );

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		NNAudioSystem::GetInstance()->Play( m_OkSound );
		// 현재 가리키고 있는 메뉴에 따라 다른 설정.
		switch (m_KeyOn)
		{
		case MENU_TEST:
			m_GameMode = TEST_MODE;
			ChangeScene();				// 테스트 모드일 경우 별 다른 설정 없이 씬 변경.
			break;
		case MENU_CLIENT:
			m_GameMode = CLIENT_MODE;
			ShowCommand(MENU_CLIENT, L"Input Server IP : ", L"Input Server IP\n  and\npress Z to start\n\n  or\npress X to cancel.");
			break;
		case MENU_SERVER:
			m_GameMode = SERVER_MODE;
			ShowCommand(MENU_SERVER, L"Your IP : ", L"Press\nZ to start,\nX to cancel");
			GetCurrentIP();
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}

void CMainMenuScene::GetCurrentIP()
{
	// 일단은 코드 안에 박아둠, 나중에 현찬이가 알아내는 함수 알려주면 바꿀 코드.
	strcpy_s(m_serverIP, _countof(m_serverIP), "127.0.0.1");
	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
}

void CMainMenuScene::GetIPInput()
{
	// for appending string. 더 나은 방법 있나 ? ㅜㅜ
	size_t len = strlen(m_serverIP);
	char* buffer = new char[len+2];
	strcpy_s(buffer, len+2, m_serverIP);

	if (NNInputSystem::GetInstance()->GetKeyState(VK_OEM_PERIOD) == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('0') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('1') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('2') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('3') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('4') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('5') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('6') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('7') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('8') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('9') == KEY_DOWN
		)
		NNAudioSystem::GetInstance()->Play( m_SelectSound );

	if ( NNInputSystem::GetInstance()->GetKeyState(VK_OEM_PERIOD) == KEY_DOWN) {buffer[len] = '.'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('0') == KEY_DOWN) {buffer[len] = '0'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('1') == KEY_DOWN) {buffer[len] = '1'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('2') == KEY_DOWN) {buffer[len] = '2'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('3') == KEY_DOWN) {buffer[len] = '3'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('4') == KEY_DOWN) {buffer[len] = '4'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('5') == KEY_DOWN) {buffer[len] = '5'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('6') == KEY_DOWN) {buffer[len] = '6'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('7') == KEY_DOWN) {buffer[len] = '7'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('8') == KEY_DOWN) {buffer[len] = '8'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('9') == KEY_DOWN) {buffer[len] = '9'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState(VK_BACK) == KEY_DOWN) {buffer[len-1] = '\0';}

	strcpy_s(m_serverIP, _countof(m_serverIP), buffer);
	SafeDelete(buffer);
	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
}

void CMainMenuScene::ShowCommand( int MenuIndex, wchar_t* command, wchar_t* instruction )
{
	// 메뉴 선택 설명
	swprintf(m_InstructionBuffer, _countof(m_InstructionBuffer), instruction);

	// 이미 나와있던 메뉴 라벨을 한 칸씩 내리고,
	for (int i = MenuIndex+1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i]->GetPosition() + NNPoint(0, LABEL_HEIGHT) );
	}

	// IP를 보여줌 : 버퍼 내용 바꾸고, 라벨 위치 변경하고, 라벨 다시 보이게 하고.
	swprintf(m_NetMenuBuffer[NET_MENU_COMMAND], _countof(m_NetMenuBuffer[NET_MENU_COMMAND]), command);
	m_NetMenuLabel[NET_MENU_COMMAND]->SetPosition( m_MenuLabel[MenuIndex]->GetPosition() + NNPoint(0.f, LABEL_HEIGHT) );
	m_NetMenuLabel[NET_MENU_COMMAND]->SetVisible(true);

	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
	m_NetMenuLabel[NET_MENU_IP_ADDR]->SetPosition( m_NetMenuLabel[NET_MENU_COMMAND]->GetPosition() + NNPoint(200.f, 0.f) );
	m_NetMenuLabel[NET_MENU_IP_ADDR]->SetVisible(true);
}

void CMainMenuScene::ChangeScene()
{
	// 다른 라벨들 다 숨기고,
	for (int i = 0; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetVisible(false);
	}
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		m_NetMenuLabel[i]->SetVisible(false);
	}
	// 로딩 중
	swprintf(m_InstructionBuffer, _countof(m_InstructionBuffer), L"Loading...");
	m_InstructionLabel->SetFontSize(LABEL_FONT_SIZE);

	m_bChangeScene = true;
}

void CMainMenuScene::CancelModeSelection()
{
	m_GameMode = MODE_NONE;

	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// 설명 라벨 초기화
	swprintf(m_InstructionBuffer, _countof(m_InstructionBuffer), L"%s\n%s", L"Press", L"Z to select");

	// 네트워크 관련 라벨 모두 숨기고,
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		m_NetMenuLabel[i]->SetVisible(false);
	}
	// IP 주소 관련 buffer 초기화
	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"");
	strcpy_s(m_serverIP, _countof(m_serverIP), "");

	// 메뉴 라벨 초기 배치
	m_MenuLabel[0]->SetPosition( width*0.5f + 60.f, height*0.5f - 60.f );
	for (int i = 1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i-1]->GetPosition() + NNPoint(0.f, LABEL_HEIGHT) );
	}
}
