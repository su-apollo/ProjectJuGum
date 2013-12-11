#include "NNConfig.h"
#include "MainMap.h"
#include "GameOption.h"
#include "NNSprite.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Satellite.h"
#include "Asteroid.h"
#include "Camera.h"

#include "NNAnimation.h"
#include "NNInputSystem.h"		// for 운석 테스트
#include "NNApplication.h"


CMainMap::CMainMap(void)
{
	m_Width = MAIN_MAP_WIDTH;
	m_Height = MAIN_MAP_HEIGHT;

	// 사각형 틀 생성
	m_MainFrame = NNRect::Create(m_Width, m_Height);
	m_MainFrame->SetPosition(0.f,0.f);
	m_MainFrame->SetColor(255.f, 255.f, 255.f);
	AddChild(m_MainFrame);

	// 맵 배경 이미지
	//문자열 배열로 만들어서 관리해야함
	m_BackGround = NNAnimation::Create( 25,	L"Sprite/background/IMG00000.jpg",
											L"Sprite/background/IMG00001.jpg",
											L"Sprite/background/IMG00002.jpg",
											L"Sprite/background/IMG00003.jpg",
											L"Sprite/background/IMG00004.jpg",
											L"Sprite/background/IMG00005.jpg",
											L"Sprite/background/IMG00006.jpg",
											L"Sprite/background/IMG00007.jpg",
											L"Sprite/background/IMG00008.jpg",
											L"Sprite/background/IMG00009.jpg",
											L"Sprite/background/IMG00010.jpg",
											L"Sprite/background/IMG00011.jpg",
											L"Sprite/background/IMG00012.jpg",
											L"Sprite/background/IMG00013.jpg",
											L"Sprite/background/IMG00014.jpg",
											L"Sprite/background/IMG00015.jpg",
											L"Sprite/background/IMG00016.jpg",
											L"Sprite/background/IMG00017.jpg",
											L"Sprite/background/IMG00018.jpg",
											L"Sprite/background/IMG00019.jpg",
											L"Sprite/background/IMG00020.jpg",
											L"Sprite/background/IMG00021.jpg",
											L"Sprite/background/IMG00022.jpg",
											L"Sprite/background/IMG00023.jpg",
											L"Sprite/background/IMG00024.jpg"
												);

	m_BackGround->SetImageWidth( GetWidth() );
	m_BackGround->SetImageHeight( GetHeight() );
	AddChild( m_BackGround );

	//플레이어 생성
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	// cost
	m_CostPerSecond = 5.f;

	// 플레이어 배치
	// (0,0) 이 맵의 중심. 플레이어 1은 아래 화면의 가운데에, 플레이어 2는 윗 화면의 가운데에 배치한다.
	m_Player1->SetPosition( 0.f, GetBotLine() *0.5f );
	m_Player2->SetPosition( 0.f, GetTopLine() *0.5f );

	AddChild( m_Player1 );
	AddChild( m_Player2 );

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
		m_Player1->GetSatelliteArray()[i] = new CSatellite;
		AddChild(m_Player1->GetSatelliteArray()[i]);
		m_Player1->GetSatelliteArray()[i]->SetVisible(false);
	}
	for (int i = 0; i <MAX_SATELLITE_NUM; ++i)
	{
		m_Player2->GetSatelliteArray()[i] = new CSatellite;
		AddChild(m_Player2->GetSatelliteArray()[i]);
		m_Player2->GetSatelliteArray()[i]->SetVisible(false);
	}

	//총알 장전
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}

	m_Camera = new CCamera();
}


CMainMap::~CMainMap(void)
{
	SafeDelete(m_Camera);
}

void CMainMap::Render()
{

	if ( m_Visible == false ) return;

	m_Matrix = D2D1::Matrix3x2F::Translation( -m_Center.GetX() , -m_Center.GetY() )* 
		D2D1::Matrix3x2F::Translation( -m_Camera->GetPositionX(), -m_Camera->GetPositionY() ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
		D2D1::Matrix3x2F::Scale( m_Camera->GetScaleX(), m_Camera->GetScaleY() ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation ) *
		D2D1::Matrix3x2F::Rotation( m_Camera->GetRotation() ) *
		D2D1::Matrix3x2F::Translation( m_Position.GetX(), m_Position.GetY() );

	if( m_pParent )
	{
		m_Matrix = m_Matrix * m_pParent->GetMatrix();
	}

	for (const auto& child : m_ChildList )
	{
		child->Render();
	}
}

void CMainMap::Update( float dTime, CFrame* frame )
{
	m_BackGround->Update(dTime);

	// cost
	GetPlayer1()->SetCost( GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	GetPlayer2()->SetCost( GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	//총알 및 오브젝트의 업데이트와 라이프타임 체크
	CBulletManager::GetInstance()->UpdateObj(dTime, m_Player2, this);

	//총알과 캐릭터의 충돌체크
	if(CBulletManager::GetInstance()->CharacterHitCheck(m_Player1))
	{
		m_Player1->SetHit( true );
	}
	//테스트 모드일 때는 적과의 충돌체크를 하지 않는다
// 	if(m_GameMode && CBulletManager::GetInstance()->CharacterHitCheck(m_Player2))
// 		m_Player2->SetHit( true );

	//캐릭터 업데이트
	m_Player1->Update(dTime, m_Player2, this, m_GameMode);
	m_Player2->UpdateByPeer(dTime, m_Player1, this, m_GameMode);

	//맵과 캐릭터의 충돌체크
	SetPlayerMoveArea(m_Player1, frame);
	SetPlayerMoveArea(m_Player2, frame);

	//운석 테스트용 코드
	if(NNInputSystem::GetInstance()->GetKeyState('P') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotAsteroid(this);
	}
}

void CMainMap::SetPlayerMoveArea( CMaincharacter * Player, CFrame* frame )
{
	// 캐릭터가 움직일 수 있는 범위. 프레임이 화면 끝까지 가지 않도록 한다.
	float leftline = GetLeftLine() - NNApplication::GetInstance()->GetLeftLine() + frame->GetLeftLine();
	float rightline = GetRightLine() - NNApplication::GetInstance()->GetRightLine() + frame->GetRightLine();
	float botline = GetBotLine() - NNApplication::GetInstance()->GetBotLine() + frame->GetBotLine();
	float topline = GetTopLine() - NNApplication::GetInstance()->GetTopLine() + frame->GetTopLine();
	
	if (Player->GetPositionX() < leftline)
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

bool CMainMap::IsGameEnd()
{
	if ( m_Player1->IsHit() || m_Player2->IsHit())
	{
		return true;
	}

	return false;
}
