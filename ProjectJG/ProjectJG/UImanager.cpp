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

#ifdef _DEBUG
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
#else
	// "SP"
	m_SPLabel = NNSprite::Create(LABEL_SP);
	m_UIList[m_UINum++] = m_SPLabel;
	m_SPLabel->SetPosition( ScreenWidth*0.5f, BotLine - 21.f - m_SPLabel->GetImageHeight()*0.5f );
#endif
	

	// char 별로 다른 것들

	// 캐릭터 그림
	m_PlayerPortrait[RAYMU] = NNSprite::Create(RAYMU_PORTRAIT);
	m_UIList[m_UINum++] = m_PlayerPortrait[RAYMU];

	m_PlayerPortrait[MARISA] = NNSprite::Create(MARISA_PORTRAIT);
	m_UIList[m_UINum++] = m_PlayerPortrait[MARISA];m_PlayerPortrait[RAYMU]->SetPosition( LeftLine + m_PlayerPortrait[RAYMU]->GetImageWidth()*0.5f, BotLine - m_PlayerPortrait[RAYMU]->GetImageHeight()*0.5f );

	// 서브 캐릭터 그림
	m_SubCharPortrait[RAYMU] = NNSprite::Create(RAYMU_SUB_PORTRAIT);
	m_UIList[m_UINum++] = m_SubCharPortrait[RAYMU];

	m_SubCharPortrait[MARISA] = NNSprite::Create(MARISA_SUB_PORTRAIT);
	m_UIList[m_UINum++] = m_SubCharPortrait[MARISA];

	// 스킬 키보드
	m_SkillKeySprite[RAYMU] = NNSprite::Create(RAYMU_KEYBOARD);
	m_UIList[m_UINum++] = m_SkillKeySprite[RAYMU];
	m_SkillKeySprite[MARISA] = NNSprite::Create(MARISA_KEYBOARD);
	m_UIList[m_UINum++] = m_SkillKeySprite[MARISA];
	for (int i = 0; i < CHAR_NUM; i++)
	{
		m_SkillKeySprite[i]->SetPosition( 283.f + m_SkillKeySprite[i]->GetImageWidth()*0.5f, BotLine - 12.f - m_SkillKeySprite[i]->GetImageHeight()*0.5f );
	}

	SetMyCharType(RAYMU);

	// 라벨 (NNSpriteAtlas : Create, SetImageWidth, SetPosition(0번을 기준으로 FONT WIDTH만큼 옆으로)

#ifdef _DEBUG
	// FPS 라벨
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
#endif	

	// cost 라벨
	for (int i = 0; i < CHAR_NUM; i++)
	{
		for (int j = 0; j < UI_COST_MAX_BUFFER_SIZE; j++)
		{
			m_PlayerCostLabel[i][j] = NNSpriteAtlas::Create(MAIN_MENU_NUMBER_FONT);
			m_PlayerCostLabel[i][j]->SetImageWidth(UI_COST_FONT_WIDTH);
			m_PlayerCostLabel[i][j]->SetImageHeight(UI_COST_FONT_HEIGHT);
		}
	}
	m_PlayerCostLabel[0][0]->SetPosition( m_SPLabel->GetPositionX() -m_SPLabel->GetImageWidth()*0.5f -25.f -UI_COST_FONT_WIDTH*0.5f -UI_COST_FONT_WIDTH*2.f,	m_SPLabel->GetPositionY() );
	m_PlayerCostLabel[1][0]->SetPosition( m_SPLabel->GetPositionX() +m_SPLabel->GetImageWidth()*0.5f +25.f +UI_COST_FONT_WIDTH*0.5f,							m_SPLabel->GetPositionY() );
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
#ifdef _DEBUG
	for (int i = 0; i < 20; i++)
	{
		SafeDelete(m_FPSLabel[i]);
	}
#endif	
}

void UImanager::Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 )
{
#ifdef _DEBUG
	// FPS
	sprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), "%0.3f", NNApplication::GetInstance()->GetFPS() );
	for (int i = 0; i < 20; i++)
	{
		SetAtlasChar(m_FPSLabel[i], m_FPSBuffer[i]);
	}
#endif
	
	// cost
#ifdef _DEBUG
	sprintf_s( m_PlayerCostBuffer[0], _countof(m_PlayerCostBuffer[0]), "%-8d", (int)(Player1->GetCost()) );
	sprintf_s( m_PlayerCostBuffer[1], _countof(m_PlayerCostBuffer[1]), "%8d", (int)(Player2->GetCost()) );
#else
	sprintf_s( m_PlayerCostBuffer[0], _countof(m_PlayerCostBuffer[0]), "%3d", (int)(Player1->GetCost()) );
	sprintf_s( m_PlayerCostBuffer[1], _countof(m_PlayerCostBuffer[1]), "%3d", (int)(Player2->GetCost()) );
#endif // _DEBUG
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
#ifdef _DEBUG
	for (int i = 0; i < 20; i++)
	{
		m_FPSLabel[i]->SetVisible(visible);
	}
#endif	
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
#ifdef _DEBUG
	for (int i = 0; i < 20; i++)
	{
		m_FPSLabel[i]->Render();
	}
#endif	
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

void UImanager::SetMyCharType(ECharcterType CharType)
{
	float LeftLine = NNApplication::GetInstance()->GetLeftLine();
	float RightLine = NNApplication::GetInstance()->GetRightLine();
	float TopLine = NNApplication::GetInstance()->GetTopLine();
	float BotLine = NNApplication::GetInstance()->GetBotLine();

	int MyChar = CharType;
	int EnemyChar = CHAR_NUM-1 - CharType;

	m_PlayerPortrait[MyChar]->SetPosition( LeftLine + m_PlayerPortrait[MyChar]->GetImageWidth()*0.5f, BotLine - m_PlayerPortrait[MyChar]->GetImageHeight()*0.5f );
	m_PlayerPortrait[EnemyChar]->SetPosition( RightLine - m_PlayerPortrait[EnemyChar]->GetImageWidth()*0.5f, BotLine - m_PlayerPortrait[EnemyChar]->GetImageHeight()*0.5f );
	m_SubCharPortrait[MyChar]->SetPosition( LeftLine + 121.f + m_SubCharPortrait[MyChar]->GetImageWidth()*0.5f, BotLine - m_SubCharPortrait[MyChar]->GetImageHeight()*0.5f );
	m_SubCharPortrait[EnemyChar]->SetPosition( RightLine - 121.f - m_SubCharPortrait[MyChar]->GetImageWidth()*0.5f, BotLine - m_SubCharPortrait[MyChar]->GetImageHeight()*0.5f );
	m_SkillKeySprite[MyChar]->SetVisible(true);
	m_SkillKeySprite[EnemyChar]->SetVisible(false);

	if (CharType == MARISA)
	{
		for (int i = 0; i < CHAR_NUM; i++) { 
			m_PlayerPortrait[i]->SetScaleX(-1);
			m_SubCharPortrait[i]->SetScaleX(-1);
		}
	}
	else
	{
		for (int i = 0; i < CHAR_NUM; i++) { 
			m_PlayerPortrait[i]->SetScaleX(1);
			m_SubCharPortrait[i]->SetScaleX(1);
		}
	}
}
