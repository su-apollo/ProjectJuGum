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
	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_FPSLabel->SetColor( 255.f, 255.f, 255.f );
	
	m_SumTime = 0;

	// cost
	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	m_Player1CostLabel->SetColor( 255.f, 255.f, 255.f );
	
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	m_Player2CostLabel->SetColor( 255.f, 255.f, 255.f );


	m_UIList[0] = m_FPSLabel;
	m_UIList[1] = m_Player1CostLabel;
	m_UIList[2] = m_Player2CostLabel;
}


UImanager::~UImanager(void)
{
}

void UImanager::Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 )
{
	// FPS
	m_SumTime += dTime;
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString( m_FPSBuffer );

	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"Player1's Cost : %d", (int)(Player1->GetCost()) );
	m_Player1CostLabel->SetString( m_Player1CostBuffer );
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"Player2's Cost : %d", (int)(Player2->GetCost()) );
	m_Player2CostLabel->SetString( m_Player2CostBuffer );
}

void UImanager::SetAllVisible( bool visible )
{
	for (int i = 0; i < 3; ++i)
	{
		m_UIList[i]->SetVisible( visible );
	}
}

void UImanager::Render()
{
	for (int i = 0; i < 3; ++i)
	{
		m_UIList[i]->Render();
	}
}
