#include "NNConfig.h"

#include "MainMenuScene.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "NNApplication.h"
#include "PlayScene.h"
#include "NNSprite.h"
#include "NNAudioSystem.h"
#include "NNNetworkSystem.h"
#include "NNSpriteAtlas.h"
#include "NNAnimation.h"

CMainMenuScene::CMainMenuScene(void)
{
	NNNetworkSystem::GetInstance()->Init();

	// BGM
	m_BackgroundSound = NNResourceManager::GetInstance()->LoadSoundFromFile( MAIN_MENU_SCENE_BACKGROUND_SOUND, true );
	NNAudioSystem::GetInstance()->Play( m_BackgroundSound );

	//effectsound
	m_OkSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_OK, false );
	m_CancelSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_CANCEL, false );
	m_SelectSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_SELECT, false );

	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// 배경 이미지
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition( width*0.5f, height*0.5f );
	m_BackGround->SetImageHeight(height);
	m_BackGround->SetImageWidth(width);
	AddChild(m_BackGround);

	// 메뉴 라벨 생성
	m_MenuLabel[MENU_TEST] = NNSprite::Create(MAIN_MENU_LABEL_TEST);
	AddChild( m_MenuLabel[MENU_TEST] );
	m_MenuLabel[MENU_SERVER] = NNSprite::Create(MAIN_MENU_LABEL_SERVER);
	AddChild( m_MenuLabel[MENU_SERVER] );
	m_MenuLabel[MENU_CLIENT] = NNSprite::Create(MAIN_MENU_LABEL_CLIENT);
	AddChild( m_MenuLabel[MENU_CLIENT] );
	m_MenuLabel[MENU_QUIT] = NNSprite::Create(MAIN_MENU_LABEL_QUIT);
	AddChild( m_MenuLabel[MENU_QUIT] );
	// 강조 라벨 생성
	m_HighlightLabel[MENU_TEST] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_TEST);
	AddChild(m_HighlightLabel[MENU_TEST], 1);	// 지금 자식들을 벡터구조로 바꾸면서 Zindex 정렬을 안 해서 의미없네?!
	m_HighlightLabel[MENU_SERVER] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_SERVER);
	AddChild(m_HighlightLabel[MENU_SERVER], 1);
	m_HighlightLabel[MENU_CLIENT] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_CLIENT);
	AddChild(m_HighlightLabel[MENU_CLIENT], 1);
	m_HighlightLabel[MENU_QUIT] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_QUIT);
	AddChild(m_HighlightLabel[MENU_QUIT], 1);

	InitMenuLabel();

	m_KeyOn = 0;				// 현재 가리키고 있는 메뉴 위치
	m_bMenuSelected = false;	// "메뉴가 아직 선택되지 않았다"


	m_InstructionLabel = NNSprite::Create(MAIN_MENU_INSTRUCTION);
	m_InstructionLabel->SetPosition( width*0.5f, height*0.3f );
	AddChild(m_InstructionLabel);

	// 네트워크 라벨 : command 생성,배치.
	m_NetMenuLabel[NET_MENU_SERVER] = NNSprite::Create(MAIN_MENU_SERVER_COMMAND);
	m_NetMenuLabel[NET_MENU_SERVER]->SetPosition(m_MenuLabel[MENU_SERVER]->GetPosition() + NNPoint(m_NetMenuLabel[NET_MENU_SERVER]->GetImageWidth()*0.5f + MAIN_MENU_LABEL_HORIZONTAL_SPACE*0.4f, -50.f));
	AddChild(m_NetMenuLabel[NET_MENU_SERVER]);

	m_NetMenuLabel[NET_MENU_CLIENT] = NNSprite::Create(MAIN_MENU_CLIENT_COMMAND);
	m_NetMenuLabel[NET_MENU_CLIENT]->SetPosition(m_MenuLabel[MENU_CLIENT]->GetPosition() + NNPoint(m_NetMenuLabel[NET_MENU_CLIENT]->GetImageWidth()*0.5f + MAIN_MENU_LABEL_HORIZONTAL_SPACE*0.4f, -50.f));
	AddChild(m_NetMenuLabel[NET_MENU_CLIENT]);

	// ipAddr 생성, 배치.
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		for (int j = 0; j < MAIN_MENU_MAX_BUFFER_SIZE; j++)
		{
			m_AddrLabel[i][j] = NNSpriteAtlas::Create(MAIN_MENU_NUMBER_FONT);
			m_AddrLabel[i][j]->SetImageWidth(MAIN_MENU_FONT_WIDTH);
			AddChild(m_AddrLabel[i][j]);
		}
		m_AddrLabel[i][0]->SetPosition(m_NetMenuLabel[i]->GetPosition() + NNPoint(-m_NetMenuLabel[i]->GetImageWidth()*0.5f, MAIN_MENU_LABEL_VERTICAL_SPACE));
		for (int j = 1; j < MAIN_MENU_MAX_BUFFER_SIZE; j++)
		{
			m_AddrLabel[i][j]->SetPosition(m_AddrLabel[i][j-1]->GetPosition() + NNPoint(MAIN_MENU_FONT_WIDTH, 0.f));
		}
	}

	m_Cursor = NNAnimation::Create(2, 0.5f, L"Sprite/font/underbar00.png", L"Sprite/font/underbar01.png");
	m_Cursor->SetPosition(m_AddrLabel[NET_MENU_CLIENT][0]->GetPosition());
	m_Cursor->SetVisible(false);
	AddChild(m_Cursor);

	InitNetworkLabel();
	
	//로딩화면
	m_Loading = NNSprite::Create( MAIN_MENU_LOADING_SCENE );
	m_Loading->SetPosition( width*0.5f, height*0.5f );
	m_Loading->SetImageHeight(height);
	m_Loading->SetImageWidth(width);
	m_Loading->SetVisible(false);
	AddChild( m_Loading );

	m_bChangeScene = false;
	m_GameMode = MODE_NONE;
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

	// 현재 선택된 게임 모드(키보드가 위치한 메뉴)에 따라 업데이트를 달리 함.
	if (!m_bMenuSelected)			// 아직 게임 모드가 설정되지 않았을 경우, 키보드(화살표) 입력에 따른 메뉴라벨 처리.
	{
		SetUpGameMode();
	}
	else {							// 게임 모드가 선택됐을 경우, // 현재 선택된 게임 모드(키보드가 위치한 메뉴)에 따라 업데이트를 달리 함.
		switch (m_KeyOn)
		{
		case MENU_TEST:				// 별 다른 처리 없이 게임 시작.
			ChangeScene();
		case MENU_SERVER:			// Z를 누르면 게임 시작, X를 누르면 메뉴선택 취소.
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
		case MENU_CLIENT:			// Z를 누르면 게임 시작, X를 누르면 메뉴선택 취소, IP입력 처리.
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
			GetIPInput(dTime);
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}

void CMainMenuScene::SetUpGameMode()
{
	m_HighlightLabel[m_KeyOn]->SetVisible(false);
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
	m_HighlightLabel[m_KeyOn]->SetVisible(true);

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		m_bMenuSelected = true;		// 메뉴가 선택됐다고 표시
		NNAudioSystem::GetInstance()->Play( m_OkSound );
		// 현재 가리키고 있는 메뉴에 따라 다른 설정 : 게임모드 설정, 메뉴에 따른 명령 표시
		switch (m_KeyOn)
		{
		case MENU_TEST:
			m_GameMode = TEST_MODE;
			break;
		case MENU_SERVER:
			m_GameMode = SERVER_MODE;
			GetCurrentIP();			// 서버모드에서는 IP주소를 바로 보여줌.
			ShowCommand(m_KeyOn, NET_MENU_SERVER);
			break;
		case MENU_CLIENT:
			m_GameMode = CLIENT_MODE;
			m_Cursor->SetVisible(true);
			ShowCommand(m_KeyOn, NET_MENU_CLIENT);
			break;
		case MENU_QUIT:
			break;
		default:
			break;
		}
	}
}

void CMainMenuScene::GetCurrentIP( int NetMenuIndex )
{
	strcpy_s(m_serverIP, _countof(m_serverIP), NNNetworkSystem::GetInstance()->GetIpAddress());
	for (int i = 0; i < MAIN_MENU_MAX_BUFFER_SIZE; i++)
	{
		if (m_serverIP[i]) { SetAtlasChar(m_AddrLabel[NetMenuIndex][i], m_serverIP[i]); m_AddrLabel[NetMenuIndex][i]->SetVisible(true); }
		else { SetAtlasChar(m_AddrLabel[NetMenuIndex][i], ' '); m_AddrLabel[NetMenuIndex][i]->SetVisible(false); }
	}
}

void CMainMenuScene::GetIPInput( float dTime, int NetMenuIndex )
{
	size_t len = strlen(m_serverIP);
	char* buffer = new char[len+2];
	strcpy_s(buffer, len+2, m_serverIP);
	bool bAdded = false;

	if ( NNInputSystem::GetInstance()->GetKeyState(VK_OEM_PERIOD) == KEY_DOWN) {buffer[len] = '.'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '.'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('0') == KEY_DOWN) {buffer[len] = '0'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '0'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('1') == KEY_DOWN) {buffer[len] = '1'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '1'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('2') == KEY_DOWN) {buffer[len] = '2'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '2'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('3') == KEY_DOWN) {buffer[len] = '3'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '3'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('4') == KEY_DOWN) {buffer[len] = '4'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '4'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('5') == KEY_DOWN) {buffer[len] = '5'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '5'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('6') == KEY_DOWN) {buffer[len] = '6'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '6'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('7') == KEY_DOWN) {buffer[len] = '7'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '7'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('8') == KEY_DOWN) {buffer[len] = '8'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '8'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState('9') == KEY_DOWN) {buffer[len] = '9'; buffer[len+1] = '\0'; SetAtlasChar(m_AddrLabel[NetMenuIndex][len], '9'); bAdded = true;}
	else if ( NNInputSystem::GetInstance()->GetKeyState(VK_BACK) == KEY_DOWN) {
		buffer[len-1] = '\0';
		SetAtlasChar(m_AddrLabel[NetMenuIndex][len-1], ' ');
		m_AddrLabel[NetMenuIndex][len-1]->SetVisible(false);
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		m_Cursor->SetPosition(m_AddrLabel[NET_MENU_CLIENT][len-1]->GetPosition());
	}

	if (bAdded)
	{
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		m_AddrLabel[NetMenuIndex][len]->SetVisible(true);
		m_Cursor->SetPosition(m_AddrLabel[NET_MENU_CLIENT][len+1]->GetPosition());
	}
	m_Cursor->Update(dTime);
	strcpy_s(m_serverIP, _countof(m_serverIP), buffer);
	SafeDelete(buffer);
}

void CMainMenuScene::ShowCommand( int MenuIndex, int NetMenuIndex )
{
	// 이미 나와있던 메뉴 라벨을 한 칸 옆으로 민다.
	for (int i = MenuIndex+1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i]->GetPosition() + NNPoint(MAIN_MENU_LABEL_HORIZONTAL_SPACE, 0.f) );
		m_HighlightLabel[i]->SetPosition( m_MenuLabel[i]->GetPosition() );
	}

	// IP를 보여준다 : 버퍼 내용 바꾸고, 라벨 위치 변경하고, 라벨 다시 보이게 하고.
	m_NetMenuLabel[NetMenuIndex]->SetVisible(true);
}

void CMainMenuScene::ChangeScene()
{
	m_Loading->SetVisible(true);
	m_bChangeScene = true;
}

void CMainMenuScene::CancelModeSelection()
{
	m_GameMode = MODE_NONE;
	m_bMenuSelected = false;

	InitMenuLabel();
	InitNetworkLabel();
}

void CMainMenuScene::InitMenuLabel()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_MenuLabel[0]->SetPosition( width*0.31f, height*0.7f );
	for (int i = 1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i-1]->GetPosition() + NNPoint(MAIN_MENU_LABEL_HORIZONTAL_SPACE, 0.f) );
	}

	for (int i = 0; i < MENU_NUM; i++)
	{
		m_HighlightLabel[i]->SetPosition(m_MenuLabel[i]->GetPosition());
		m_HighlightLabel[i]->SetVisible(false);
	}
}

void CMainMenuScene::InitNetworkLabel()
{
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		m_NetMenuLabel[i]->SetVisible(false);
		for (int j = 0; j < MAIN_MENU_MAX_BUFFER_SIZE; j++)
		{
			//SetAtlasChar(m_AddrLabel[i][j], ' ');
			m_AddrLabel[i][j]->SetVisible(false);
		}
	}
	strcpy_s(m_serverIP, _countof(m_serverIP), "");
	
}

void CMainMenuScene::SetAtlasChar( NNSpriteAtlas* atlas, char number )
{
	char NumberArray[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ' '};
	int length = sizeof(NumberArray)/sizeof(NumberArray[0]);
	for (int i = 0; i < length; i++)
	{
		if (number == NumberArray[i])
		{
			atlas->SetCutSize(MAIN_MENU_FONT_WIDTH*i, 0, MAIN_MENU_FONT_WIDTH*(i+1), MAIN_MENU_FONT_WIDTH);
			return;
		}
	}
	atlas->SetCutSize(MAIN_MENU_FONT_WIDTH*length, 0, MAIN_MENU_FONT_WIDTH*(length+1), MAIN_MENU_FONT_WIDTH);
}
