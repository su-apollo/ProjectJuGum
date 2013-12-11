#include "NNConfig.h"
#include "NNApplication.h"
#include "NNLabel.h"
#include "NNInputSystem.h"

#include "UImanager.h"

#include "Maincharacter.h"

UImanager* UImanager::m_pInstance = nullptr;

UImanager* UImanager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new UImanager();
	}

	return m_pInstance;
}

void UImanager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

UImanager::UImanager(void)
{
	m_UINum = 0;		// UI 개수 카운트

	// FPS
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : " );
	m_FPSLabel = NNLabel::Create( m_FPSBuffer, GAME_FONT, 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_UIList[m_UINum++] = m_FPSLabel;

	// cost
	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"Player1's Cost : " );
	m_Player1CostLabel = NNLabel::Create( m_Player1CostBuffer, GAME_FONT, 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	m_UIList[m_UINum++] = m_Player1CostLabel;
	
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"Player2's Cost : " );
	m_Player2CostLabel = NNLabel::Create( m_Player2CostBuffer, GAME_FONT, 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	m_UIList[m_UINum++] = m_Player2CostLabel;

	// Network Menu
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_NetworkMenuLabel[TEST_MODE] = NNLabel::Create( L"TEST", GAME_FONT, 40.f );
	m_NetworkMenuLabel[TEST_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_NetworkMenuLabel[TEST_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f );
	m_UIList[m_UINum++] = m_NetworkMenuLabel[TEST_MODE];

	m_NetworkMenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", GAME_FONT, 40.f );
	m_NetworkMenuLabel[CLIENT_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_NetworkMenuLabel[CLIENT_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f + 80.f );
	m_UIList[m_UINum++] = m_NetworkMenuLabel[CLIENT_MODE];

	m_NetworkMenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", GAME_FONT, 40.f );
	m_NetworkMenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_NetworkMenuLabel[SERVER_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f + 160.f );
	m_UIList[m_UINum++] = m_NetworkMenuLabel[SERVER_MODE];

	m_KeyOn = 0;

	SetAllVisible(false);
}


UImanager::~UImanager(void)
{
	for (int i = 0; i < m_UINum; ++i)
	{
		SafeDelete(m_UIList[i]);
	}
}

void UImanager::Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 )
{
	// FPS
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );

	// cost
	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"Player1's Cost : %d", (int)(Player1->GetCost()) );
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"Player2's Cost : %d", (int)(Player2->GetCost()) );
}

void UImanager::SetAllVisible( bool visible )
{
	for (int i = 0; i < m_UINum; ++i)
	{
		m_UIList[i]->SetVisible( visible );
	}
}

void UImanager::Render()
{
	for (int i = 0; i < m_UINum; ++i)
	{
		m_UIList[i]->Render();
	}
}

ENetworkMode UImanager::NetworkMenuUpdate()
{
	m_NetworkMenuLabel[m_KeyOn]->SetColor( 0.f, 0.f, 0.f);	
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
	m_NetworkMenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f );

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
		return (ENetworkMode)m_KeyOn;
	else return (ENetworkMode)NET_MENU_NONE;
}

void UImanager::SetNetworkMenuVisible( bool visible )
{
	for (int i = NET_MENU_FIRST; i < NET_MENU_LAST; ++i)
	{
		m_NetworkMenuLabel[i]->SetVisible(visible);
	}
}
