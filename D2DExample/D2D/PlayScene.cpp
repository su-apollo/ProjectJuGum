#include "PlayScene.h"
#include "MainMenuScene.h"

CPlayScene::CPlayScene(void)
{
	//맵생성
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	//플레이어 생성
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	m_Player2->SetKeyUp('W');
	m_Player2->SetKeyDown('S');
	m_Player2->SetKeyLeft('A');
	m_Player2->SetKeyRight('D');

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
	// 1초는 너무 길길래 0.2초로 줄임
	if ( m_SumTime > 0.2 )
	{
	swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString(m_FPS);
		// 밑의 두 줄 중에 어느 게 더 나은 지 모르겠다 ㅜㅜ
		// 0.2 초 한 번 찍고 난 다음엔 리셋(=0) 되는 게 나은 듯.
		 m_SumTime = 0;
		// m_SumTime -= 0.2;
	}

	//공격입력
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SPACE ) == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotBullet(m_Player1);
	}

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
