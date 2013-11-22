#include "NNConfig.h"

#include "NNLabel.h"
#include "NNSceneDirector.h"
#include "NNApplication.h"
#include "NNSprite.h"

#include "PlayScene.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "MainMenuScene.h"
#include "MainMap.h"
#include "ReturnScene.h"

CPlayScene::CPlayScene(void)
{
	// ÇÃ·¹ÀÌ ¾À ÀüÃ¼ È­¸é ¹è°æ ÀÌ¹ÌÁö
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition(NNPoint( (float)NNApplication::GetInstance()->GetScreenWidth()/2, (float)NNApplication::GetInstance()->GetScreenHeight()/2));
	m_BackGround->SetImageHeight( (float)NNApplication::GetInstance()->GetScreenHeight());
	m_BackGround->SetImageWidth( (float)NNApplication::GetInstance()->GetScreenWidth());
	AddChild(m_BackGround);

	//¸Ê»ý¼º
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"¸¼Àº °íµñ", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	m_FPSLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;

	// cost
	m_Map->GetPlayer1()->SetCost(10000);
	m_Map->GetPlayer2()->SetCost(0);
	
	m_CostPerSecond = 5.f;
	
	m_Player1CostLabel = NNLabel::Create( L"Player1's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player1CostLabel->SetPosition( 0.f, 700.f );
	m_Player1CostLabel->SetColor( 255.f, 255.f, 255.f );
	AddChild( m_Player1CostLabel );
	m_Player2CostLabel = NNLabel::Create( L"Player2's Cost : ", L"¸¼Àº °íµñ", 20.f );
	m_Player2CostLabel->SetPosition( 0.f, 100.f );
	m_Player2CostLabel->SetColor( 255.f, 255.f, 255.f );
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
	swprintf_s( m_FPSBuffer, _countof(m_FPSBuffer), L"FPS : %0.3f", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString( m_FPSBuffer );


	// cost
	m_Map->GetPlayer1()->SetCost( m_Map->GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	m_Map->GetPlayer2()->SetCost( m_Map->GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	swprintf_s( m_Player1CostBuffer, _countof(m_Player1CostBuffer), L"Player1's Cost : %d", (int)(m_Map->GetPlayer1()->GetCost()) );
	m_Player1CostLabel->SetString( m_Player1CostBuffer );
	swprintf_s( m_Player2CostBuffer, _countof(m_Player2CostBuffer), L"Player2's Cost : %d", (int)(m_Map->GetPlayer2()->GetCost()) );
	m_Player2CostLabel->SetString( m_Player2CostBuffer );


	// ¾À¿¡¼­ Ã³¸®ÇÏ´ø ¸ðµç Ã³¸®¸¦ ¸ÞÀÎ ¸ÊÀ¸·Î ³Ñ±è.
	m_Map->Update( dTime );
	if ( m_Map->IsGameEnd() ) EndGame();
}

bool CPlayScene::CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B) 
{
	if((radius_A + radius_B) > point_A.GetDistance(point_B))
	{
		return true;
	}
	return false;
}

void CPlayScene::EndGame()
{
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
	return;
}
