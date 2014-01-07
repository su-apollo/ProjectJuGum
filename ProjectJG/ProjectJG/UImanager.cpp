#include "NNConfig.h"
#include "GameOption.h"
#include "NNApplication.h"
#include "NNLabel.h"

#include "UImanager.h"

#include "Maincharacter.h"
#include "NNSpriteAtlas.h"
#include "NNLabel.h"


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
	m_time->SetImageHeight(m_time->GetImageHeight() * 1.5f);
	m_time->SetImageWidth(m_time->GetImageWidth() * 1.5f);
	m_time->SetPosition( ScreenWidth*0.5f - 15.f, BotLine - m_time->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_time;

	swprintf(m_TimeBuffer, _countof(m_TimeBuffer), L"00:00"); 
	m_TimeLabel = NNLabel::Create(m_TimeBuffer, L"맑은 고딕", 20.f);
	m_TimeLabel->SetPosition(m_time->GetPosition() - NNPoint(30.f, 10.f));
	m_UIList[m_UINum++] = m_TimeLabel;

	// 캐릭터 그림
	m_PlayerPortrait[RAYMU] = NNSprite::Create(RAYMU_PORTRAIT);
	m_PlayerPortrait[RAYMU]->SetImageWidth(m_PlayerPortrait[RAYMU]->GetImageWidth()*0.4f);
	m_PlayerPortrait[RAYMU]->SetImageHeight(m_PlayerPortrait[RAYMU]->GetImageHeight()*0.4f);
	m_PlayerPortrait[RAYMU]->SetPosition( LeftLine + m_PlayerPortrait[RAYMU]->GetImageWidth()*0.5f, BotLine - m_PlayerPortrait[RAYMU]->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_PlayerPortrait[RAYMU];

	m_PlayerPortrait[MARISA] = NNSprite::Create(MARISA_PORTRAIT);
	m_PlayerPortrait[MARISA]->SetImageWidth(m_PlayerPortrait[MARISA]->GetImageWidth()*0.4f);
	m_PlayerPortrait[MARISA]->SetImageHeight(m_PlayerPortrait[MARISA]->GetImageHeight()*0.4f);
	m_PlayerPortrait[MARISA]->SetPosition( RightLine - m_PlayerPortrait[MARISA]->GetImageWidth()*0.5f, BotLine - m_PlayerPortrait[MARISA]->GetImageHeight()*0.5f );
	m_UIList[m_UINum++] = m_PlayerPortrait[MARISA];

	// 라벨 (NNSpriteAtlas : Create, SetImageWidth, SetPosition(0번을 기준으로 FONT WIDTH만큼 옆으로)

	// FPS
	m_FPSSprite = NNSprite::Create(LABEL_FPS);
	m_FPSSprite->SetPosition(m_FPSSprite->GetImageWidth()*0.5f, m_FPSSprite->GetImageHeight()*0.5f);
	m_UIList[m_UINum++] = m_FPSSprite;

	for (int i = 0; i < 20; i++)
	{
		m_FPSLabel[i] = NNSpriteAtlas::Create(MAIN_MENU_NUMBER_FONT);
		m_FPSLabel[i]->SetImageWidth(UI_FPS_FONT_WIDTH);
		m_FPSLabel[i]->SetImageHeight(UI_FPS_FONT_HEIGHT);
	}
	m_FPSLabel[0]->SetPosition( m_FPSSprite->GetPosition() + NNPoint(m_FPSSprite->GetImageWidth()*0.5f + 10.f, 0.f) );
	for (int i = 1; i < 20; i++)
	{
		m_FPSLabel[i]->SetPosition(m_FPSLabel[i-1]->GetPosition() + NNPoint(UI_FPS_FONT_WIDTH, 0.f));
	}

	// cost
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			m_PlayerCostLabel[i][j] = NNSpriteAtlas::Create(MAIN_MENU_NUMBER_FONT);
			m_PlayerCostLabel[i][j]->SetImageWidth(UI_COST_FONT_WIDTH);
			m_PlayerCostLabel[i][j]->SetImageHeight(UI_COST_FONT_HEIGHT);
		}
	}

	m_PlayerCostLabel[RAYMU][0]->SetPosition( m_PlayerPortrait[RAYMU]->GetPosition() + NNPoint( m_PlayerPortrait[RAYMU]->GetImageWidth()*0.5f + 50.f, 40.f ) );
	m_PlayerCostLabel[MARISA][0]->SetPosition( m_PlayerPortrait[MARISA]->GetPosition() + NNPoint( -m_PlayerPortrait[MARISA]->GetImageWidth()*0.5f - 20.f - UI_COST_FONT_WIDTH*8.f, 40.f ) );
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 1; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			m_PlayerCostLabel[i][j]->SetPosition(m_PlayerCostLabel[i][j-1]->GetPosition() + NNPoint(UI_COST_FONT_WIDTH, 0.f));
		}
	}
}


UImanager::~UImanager(void)
{
	for (int i = 0; i < m_UINum; ++i)
	{
		SafeDelete(m_UIList[i]);
	}
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			SafeDelete(m_PlayerCostLabel[i][j]);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		SafeDelete(m_FPSLabel[i]);
	}
}

void UImanager::Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 )
{
	// FPS
	sprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), "%0.3f", NNApplication::GetInstance()->GetFPS() );
	for (int i = 0; i < 20; i++)
	{
		SetAtlasChar(m_FPSLabel[i], m_FPSBuffer[i]);
	}

	// cost
	sprintf_s( m_PlayerCostBuffer[0], _countof(m_PlayerCostBuffer[0]), "%-8d", (int)(Player1->GetCost()) );
	sprintf_s( m_PlayerCostBuffer[1], _countof(m_PlayerCostBuffer[1]), "%8d", (int)(Player2->GetCost()) );
	for (int i = 0; i < CHAR_NUM; i++)
	{
		
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			SetAtlasChar(m_PlayerCostLabel[i][j], m_PlayerCostBuffer[i][j]);
		}
	}
}

void UImanager::SetAllVisible( bool visible )
{
	for (int i = 0; i < m_UINum; ++i)
	{
		m_UIList[i]->SetVisible( visible );
	}
	for (int i = 0; i < 20; i++)
	{
		m_FPSLabel[i]->SetVisible(visible);
	}
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			m_PlayerCostLabel[i][j]->SetVisible(visible);
		}
	}
}

void UImanager::Render()
{
	for (int i = 0; i < m_UINum; ++i)
	{
		m_UIList[i]->Render();
	}
	for (int i = 0; i < 20; i++)
	{
		m_FPSLabel[i]->Render();
	}
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			m_PlayerCostLabel[i][j]->Render();
		}
	}
}

void UImanager::SetAtlasChar( NNSpriteAtlas* atlas, char number )
{
	char NumberArray[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ':', ' '};
	int length = sizeof(NumberArray)/sizeof(NumberArray[0]);
	for (int i = 0; i < length; i++)
	{
		if (number == NumberArray[i])
		{
			atlas->SetCutSize(FONT_DEFAULT_WIDTH*i, 0, FONT_DEFAULT_WIDTH*(i+1), FONT_DEFAULT_HEIGHT);
			return;
		}
	}
	SetAtlasChar(atlas, ' ');
	//atlas->SetCutSize(MAIN_MENU_FONT_WIDTH*(length-1), 0, MAIN_MENU_FONT_WIDTH*length, MAIN_MENU_FONT_HEIGHT);
}

void UImanager::RotateCharPortrait()
{
	printf_s("Rotated Character.\n");
	NNPoint temp = m_PlayerPortrait[0]->GetPosition();
	for (int i = 0; i < CHAR_NUM; i++) { 
		m_PlayerPortrait[i]->SetScaleX(-1);

		if(i+1 == CHAR_NUM) continue;
		m_PlayerPortrait[i]->SetPosition(m_PlayerPortrait[i+1]->GetPosition());
	}
	m_PlayerPortrait[CHAR_NUM-1]->SetPosition(temp);
}

void UImanager::Init()
{

}
