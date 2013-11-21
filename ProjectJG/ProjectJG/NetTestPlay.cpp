#include "NNConfig.h"
#include "NetTestPlay.h"

#include "NNLabel.h"
#include "NNSceneDirector.h"
#include "NNApplication.h"

#include "Maincharacter.h"
#include "BulletManager.h"
#include "MainMenuScene.h"
#include "MainMap.h"
#include "ReturnScene.h"
#include "Bullet.h"
#include "Satellite.h"
#include "Asteroid.h"

CNetTestPlay::CNetTestPlay(ENetworkMode network_mode)
{
	//맵생성
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	//플레이어 생성
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	if(network_mode == SERVER_MODE)
	{
		m_Player1->SetPosition(NNPoint(640.f, 700.f));
		m_Player2->SetPosition(NNPoint(640.f, 100.f));
	}
	else
	{
		m_Player1->SetPosition(NNPoint(640.f, 100.f));
		m_Player2->SetPosition(NNPoint(640.f, 700.f));
	}

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	//총알 장전
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}

	//운석 로딩
	for (int i = 0 ; i < MAX_ASTEROID_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetAsteroidArray()[i] = new CAsteroid;
		AddChild( CBulletManager::GetInstance()->GetAsteroidArray()[i] );
		CBulletManager::GetInstance()->GetAsteroidArray()[i]->SetVisible(false);
	}

	//인공위성 로딩
	for (int i = 0; i <MAX_SATELLITE_NUM; ++i)
	{
		CBulletManager::GetInstance()->GetSatelliteArray()[i] = new CSatellite;
		AddChild( CBulletManager::GetInstance()->GetSatelliteArray()[i]);
		CBulletManager::GetInstance()->GetSatelliteArray()[i]->SetVisible(false);
	}

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"맑은 고딕", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;

	// cost
	m_Player1->SetCost(10000);

	m_CostPerSecond = 5.f;

	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"맑은 고딕", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	AddChild( m_Player1CostLabel );
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"맑은 고딕", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	AddChild( m_Player2CostLabel );
}


CNetTestPlay::~CNetTestPlay(void)
{
}

void CNetTestPlay::Render()
{
	NNScene::Render();
}
void CNetTestPlay::Update( float dTime )
{
	++m_CurrentFrame;

	if ( NNInputSystem::GetInstance()->GetMenuKeyInput() == PAUSE )
	{
		//NNSceneDirector::GetInstance()->ChangeScene( new CReturnScene() );
	}

	// FPS
	m_SumTime += dTime;
	swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString( m_FPS );


	// cost
	m_Player1->SetCost( m_Player1->GetCost() + m_CostPerSecond*dTime );
	m_Player2->SetCost( m_Player2->GetCost() + m_CostPerSecond*dTime );

	swprintf_s( m_Player1Cost, _countof(m_Player1Cost), L"Player1's Cost : %d", (int)(m_Player1->GetCost()) );
	m_Player1CostLabel->SetString( m_Player1Cost );
	swprintf_s( m_Player2Cost, _countof(m_Player2Cost), L"Player2's Cost : %d", (int)(m_Player2->GetCost()) );
	m_Player2CostLabel->SetString( m_Player2Cost );


	//총알 및 오브젝트의 업데이트와 라이프타임 채크
	CBulletManager::GetInstance()->UpdateObj(dTime, m_Player2, m_Map);

	//캐릭터 업데이트
	m_Player1->Update_NetworkMode(dTime,m_Player1, m_Player2, m_Map, m_CurrentFrame);
	m_Player2->UpdateEnemyMotion_NetworkMode(dTime, m_CurrentFrame);

	//맵과 캐릭터의 충돌체크
	SetPlayerMoveArea(m_Player1);
	//SetPlayerMoveArea(m_Player2);

	//총알과 캐릭터의 충돌체크
	if(CBulletManager::GetInstance()->CharacterHitCheck(m_Player1))
	{
		NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
		return;
	}

	//운석 테스트용 코드
	if(NNInputSystem::GetInstance()->GetKeyState('P') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotAsteroid(m_Map);
	}

}

bool CNetTestPlay::CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B) 
{
	if((radius_A + radius_B) > point_A.GetDistance(point_B))
	{
		return true;
	}
	return false;
}

void CNetTestPlay::SetPlayerMoveArea(CMaincharacter * Player)
{
	float leftline = m_Map->GetLeftLine();
	float rightline = m_Map->GetRightLine();
	float botline = m_Map->GetBotLine();
	float topline = m_Map->GetTopLine();

	if (Player->GetPositionX() < leftline )
	{
		Player->SetPosition(NNPoint(leftline, Player->GetPositionY()));
	}
	if (Player->GetPositionX() > rightline)
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
