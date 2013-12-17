#include "NNConfig.h"
#include "NNApplication.h"
#include "NNLabel.h"

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
