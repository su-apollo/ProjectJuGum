#include "NNConfig.h"
#include "NetSettingScene.h"

#include "NetTestPlay.h"
#include "NNApplication.h"
#include "NNLabel.h"
#include "NNP2PNetManager.h"
#include "PlayScene.h"

CNetSettingScene::CNetSettingScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_MenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[CLIENT_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_MenuLabel[CLIENT_MODE]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[CLIENT_MODE] );

	m_MenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", L"±Ã¼­Ã¼", 40.f );
	m_MenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[SERVER_MODE]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[SERVER_MODE] );

	m_Wait = NNLabel::Create( L"±â´Ù·Á...(Çü ±Ã¼­Ã¼´Ù)", L"±Ã¼­Ã¼", 40.f );
	m_Wait->SetColor(0.0f, 0.0f, 0.0f);
	m_Wait->SetPosition( 0.f, 0.f );
	AddChild( m_Wait );

	m_Error = NNLabel::Create( L"¹º°¡ ÀÌ»óÇÏ´Ù... ´©±¸³Ä ³Í", L"±Ã¼­Ã¼", 40.f );
	m_Error->SetColor(0.0f, 0.0f, 0.0f);
	m_Error->SetPosition( 0.f, 80.f );
	AddChild( m_Error );

	m_KeyOn = CLIENT_MODE;
}


CNetSettingScene::~CNetSettingScene(void)
{
}

void CNetSettingScene::Render()
{
	NNObject::Render();
}

void CNetSettingScene::Update( float dTime )
{
	char* serverIpAddr = "127.0.0.1";

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
			GNetHelper = new NNP2PNetHelper(false, serverIpAddr) ;

			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return;
			}

			NNSceneDirector::GetInstance()->ChangeScene( new CNetTestPlay(CLIENT_MODE) );
			break;

		case SERVER_MODE:
			GNetHelper = new NNP2PNetHelper(true, serverIpAddr) ;

			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return;
			}

			if ( !GNetHelper->DoHandShake() )
			{
				return;
			}

			NNSceneDirector::GetInstance()->ChangeScene( new CNetTestPlay(SERVER_MODE) );
			break;
		default:
			break;
		}
	}
}
