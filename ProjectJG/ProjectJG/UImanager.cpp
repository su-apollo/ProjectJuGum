#include "NNConfig.h"
#include "NNApplication.h"
#include "NNLabel.h"

#include "GameOption.h"
#include "Maincharacter.h"
#include "FontNode.h"

#include "UImanager.h"

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
	
	int index;

	// FPS
	index = 0;
	m_FPSLabel = new CFontNode();
	m_FPSValue = new CFontNode();
	m_FPSLabel->ChangeLetter(index++, FONT_ALPHABET_F);
	m_FPSLabel->ChangeLetter(index++, FONT_ALPHABET_P);
	m_FPSLabel->ChangeLetter(index++, FONT_ALPHABET_S);
	m_FPSLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_FPSLabel->ChangeLetter(index++, FONT_MARK_CONLON);
	m_FPSLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_FPSLabel->SetPosition(10.f, 0.f);
	m_FPSValue->SetPosition( m_FPSLabel->GetPosition() + NNPoint((float)index*FONT_WIDTH, 0.f) );
	m_UIList[m_UINum++] = m_FPSLabel;
	m_UIList[m_UINum++] = m_FPSValue;

	// Player1's cost
	index = 0;
	m_Player1CostLabel = new CFontNode();
	m_Player1CostValue = new CFontNode();
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_P);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_L);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_A);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_Y);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_E);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_R);
	m_Player1CostLabel->ChangeLetter(index++, FONT_NUM_1);
	m_Player1CostLabel->ChangeLetter(index++, FONT_MARK_SINGLE_QUOTATION);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_S);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_C);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_O);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_S);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_T);
	m_Player1CostLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_Player1CostLabel->ChangeLetter(index++, FONT_MARK_CONLON);
	m_Player1CostLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_Player1CostLabel->SetPosition(10.f, 700.f);
	m_Player1CostValue->SetPosition( m_Player1CostLabel->GetPosition() + NNPoint(0.f, (float)FONT_HEIGHT +1) );
	m_UIList[m_UINum++] = m_Player1CostLabel;
	m_UIList[m_UINum++] = m_Player1CostValue;
	
	// Player2's cost
	index = 0;
	m_Player2CostLabel = new CFontNode();
	m_Player2CostValue = new CFontNode();
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_P);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_L);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_A);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_Y);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_E);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_R);
	m_Player2CostLabel->ChangeLetter(index++, FONT_NUM_2);
	m_Player2CostLabel->ChangeLetter(index++, FONT_MARK_SINGLE_QUOTATION);
	m_Player1CostLabel->ChangeLetter(index++, FONT_ALPHABET_S);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_C);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_O);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_S);
	m_Player2CostLabel->ChangeLetter(index++, FONT_ALPHABET_T);
	m_Player2CostLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_Player2CostLabel->ChangeLetter(index++, FONT_MARK_CONLON);
	m_Player2CostLabel->ChangeLetter(index++, FONT_MARK_SPACE);
	m_Player2CostLabel->SetPosition(10.f, 100.f);
	m_Player2CostValue->SetPosition( m_Player2CostLabel->GetPosition() + NNPoint(0.f, (float)FONT_HEIGHT +1) );
	m_UIList[m_UINum++] = m_Player2CostLabel;
	m_UIList[m_UINum++] = m_Player2CostValue;
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
	// '\n' : 배열의 끝을 구분하기 위해....
	// FPS
	wchar_t buffer[20];
	swprintf_s( buffer, _countof(buffer), L"%0.3f\n", NNApplication::GetInstance()->GetFPS() );
	printf_s("fps : %0.3f\n", NNApplication::GetInstance()->GetFPS());
	for (int i = 0; i < _countof(buffer); i++)
	{
		if (buffer[i]=='\n') {break;}
		(buffer[i]==L'.') ? m_FPSValue->ChangeLetter(i, FONT_MARK_PEROID) : m_FPSValue->ChangeLetter(i, FONT_NUM_START+buffer[i]-'0');
	}

	// cost
	swprintf_s( buffer, _countof(buffer), L"%d\n", (int)(Player1->GetCost()) );
	printf_s("1cost : %d\n", (int)(Player1->GetCost()));
	for (int i = 0; i < _countof(buffer); i++)
	{
		if (buffer[i]=='\n') {break;}
		m_Player1CostValue->ChangeLetter(i, FONT_NUM_START+buffer[i]-'0');
	}

	swprintf_s( buffer, _countof(buffer), L"%d\n", (int)(Player2->GetCost()) );
	printf_s("2cost : %d\n", (int)(Player2->GetCost()));
	for (int i = 0; i < _countof(buffer); i++)
	{
		if (buffer[i]=='\n') {break;}
		m_Player2CostValue->ChangeLetter(i, FONT_NUM_START+buffer[i]-'0');
	}
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
