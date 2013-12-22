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
	float LeftLine = NNApplication::GetInstance()->GetLeftLine();
	float RightLine = NNApplication::GetInstance()->GetRightLine();
	float TopLine = NNApplication::GetInstance()->GetTopLine();
	float BotLine = NNApplication::GetInstance()->GetBotLine();
	float ScreenWidth = RightLine - LeftLine;
	float ScreenHeight = BotLine - TopLine;

	m_UINum = 0;		// UI 개수 카운트

	// 장식

	// 꽃 무늬
	m_flower = NNSprite::Create(BACKGROUND_FLOWER);
	m_flower->SetPosition( ScreenWidth*0.5f, TopLine + m_flower->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_flower;

	// 캐릭터 그림 배경 패턴
	m_pattern = NNSprite::Create(BACKGROUND_PATTERN);
	m_pattern->SetPosition( ScreenWidth*0.5f, BotLine - m_pattern->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_pattern;

	// 시간 배경
	m_time = NNSprite::Create(BACKGROUND_TIME);
	m_time->SetImageHeight(m_time->GetImageHeight() * 2.f);
	m_time->SetImageWidth(m_time->GetImageWidth() * 2.f);
	m_time->SetPosition( ScreenWidth*0.5f, BotLine - m_time->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_time;

	// 캐릭터 그림
	m_Player1Portrait = NNSprite::Create(RAYMU_PORTRAIT);
	m_Player1Portrait->SetImageWidth(m_Player1Portrait->GetImageWidth()*0.4f);
	m_Player1Portrait->SetImageHeight(m_Player1Portrait->GetImageHeight()*0.4f);
	m_Player1Portrait->SetPosition( LeftLine + m_Player1Portrait->GetImageWidth()*0.5f, BotLine - m_Player1Portrait->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_Player1Portrait;

	m_Player2Portrait = NNSprite::Create(MARISA_PORTRAIT);
	m_Player2Portrait->SetImageWidth(m_Player2Portrait->GetImageWidth()*0.4f);
	m_Player2Portrait->SetImageHeight(m_Player2Portrait->GetImageHeight()*0.4f);
	m_Player2Portrait->SetPosition( RightLine - m_Player2Portrait->GetImageWidth()*0.5f, BotLine - m_Player2Portrait->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_Player2Portrait;

	// 라벨

	// FPS
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : " );
	m_FPSLabel = NNLabel::Create( m_FPSBuffer, GAME_FONT, UI_LABEL_FONT_SIZE );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_UIList[m_UINum++] = m_FPSLabel;

	// cost
	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"" );
	m_Player1CostLabel = NNLabel::Create( m_Player1CostBuffer, GAME_FONT, UI_LABEL_FONT_SIZE );
	m_Player1CostLabel->SetPosition( m_Player1Portrait->GetPosition() + NNPoint( m_Player1Portrait->GetImageWidth() *0.5f + 30.f, -20.f ) );
	m_UIList[m_UINum++] = m_Player1CostLabel;

	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"" );
	m_Player2CostLabel = NNLabel::Create( m_Player2CostBuffer, GAME_FONT, UI_LABEL_FONT_SIZE );
	m_Player2CostLabel->SetPosition( m_Player2Portrait->GetPosition() + NNPoint( -m_Player2Portrait->GetImageWidth() *0.5f - 120.f, -20.f ) );
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
	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"%-8d", (int)(Player1->GetCost()) );
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"%8d", (int)(Player2->GetCost()) );
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
