#include "PlayScene.h"

CPlayScene::CPlayScene(void)
{
	//맵생성
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	//플레이어 생성
	m_Player1 = new CFirstModeCharic;
	m_Player2 = new CMaincharacter;

// 	m_Player2->SetKeyUp('W');
// 	m_Player2->SetKeyDown('S');
// 	m_Player2->SetKeyLeft('A');
// 	m_Player2->SetKeyRight('D');

	m_Player1->SetPosition(NNPoint(640.f, 700.f));
	m_Player2->SetPosition(NNPoint(640.f, 100.f));

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	//총알 장전
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}


	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"맑은 고딕", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;


	// cost

	m_Player1->SetCost(0);
	m_Player2->SetCost(0);
	
	m_CostPerSecond = 0.5;
	
	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"맑은 고딕", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	AddChild( m_Player1CostLabel );
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"맑은 고딕", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	AddChild( m_Player2CostLabel );
}

CPlayScene::~CPlayScene(void)
{
}

void CPlayScene::Render()
{
	NNScene::Render();
}
void CPlayScene::Update( float dTime )
{

	// FPS
	m_SumTime += dTime;
	if ( m_SumTime > 0.2 )
	{
		swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );
		m_FPSLabel->SetString( m_FPS );
		m_SumTime = 0;
	}


	// cost

	m_Player1->SetCost( m_Player1->GetCost() + m_CostPerSecond*dTime );
	m_Player2->SetCost( m_Player2->GetCost() + m_CostPerSecond*dTime );

	swprintf_s( m_Player1Cost, _countof(m_Player1Cost), L"Player1's Cost : %d", (int)(m_Player1->GetCost()) );
	m_Player1CostLabel->SetString( m_Player1Cost );
	swprintf_s( m_Player2Cost, _countof(m_Player2Cost), L"Player2's Cost : %d", (int)(m_Player2->GetCost()) );
	m_Player2CostLabel->SetString( m_Player2Cost );


	//공격입력
	m_Player1->SkillCasting(m_Player1);
	

	//총알의 이동
	CBulletManager::GetInstance()->UpdateBullet(dTime);

	//캐릭터의 이동
	m_Player1->Update(dTime);
	m_Player2->Update(dTime);

	//맵과 캐릭터의 충돌체크
	SetPlayerMoveArea(m_Player1);
	SetPlayerMoveArea(m_Player2);

	//총알과 캐릭터의 충돌체크
	CBulletManager::GetInstance()->CharacterHitCheck(m_Player1);
	CBulletManager::GetInstance()->CharacterHitCheck(m_Player2);
	
	//총알의 라이프타임 처리
	CBulletManager::GetInstance()->CheckBulletLifeTime(m_Map);
}

bool CPlayScene::CircleToCircleHitCheck(NNPoint Apoint, float Aradius, NNPoint Bpoint, float Bradius) 
{
	if((Aradius + Bradius) > Apoint.GetDistance(Bpoint))
	{
		return true;
	}
	return false;
}

void CPlayScene::SetPlayerMoveArea(CMaincharacter * Player)
{
	float leftline = m_Map->GetPositionX() + m_Map->GetMainFrame()->GetWidth()/2;
	float rightline = m_Map->GetPositionX() - m_Map->GetMainFrame()->GetWidth()/2;
	float botline = m_Map->GetPositionY() + m_Map->GetMainFrame()->GetHeight()/2;
	float topline = m_Map->GetPositionY() - m_Map->GetMainFrame()->GetHeight()/2;

	if (Player->GetPositionX() > leftline )
	{
		Player->SetPosition(NNPoint(leftline, Player->GetPositionY()));
	}
	if (Player->GetPositionX() < rightline)
	{
		Player->SetPosition(NNPoint(rightline, Player->GetPositionY()));
	}
	if (Player->GetPositionY() > botline)
	{
		Player->SetPosition(NNPoint(Player->GetPositionX(), botline));
	}
	if (Player->GetPositionY() < topline)
	{
		Player->SetPosition(NNPoint(Player->GetPositionX(),topline));
	}
}
