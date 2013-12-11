#include "NNConfig.h"
#include "NNNetworkSystem.h"
#include "NNApplication.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "NNInputSystem.h"
#include "NNCircle.h"
#include "NNSpriteAtlas.h"
#include "Satellite.h"
#include "PacketHandler.h"
#include "NNAnimation.h"


CMaincharacter::CMaincharacter(void) : m_bHit(false), m_SatelliteIndex(0), m_Syntime(0.f)
{
	m_Texture =  NNSpriteAtlas::Create(L"Sprite/warrior2_0.png");
	m_Texture->SetImageHeight(50.f);
	m_Texture->SetImageWidth(50.f);
	m_Texture->SetPosition(0.f, 0.f);
	AddChild( m_Texture );

	SetHitRadius(CHAR_HIT_RADIUS);
	m_Circle = NNCircle::Create(GetHitRadius());
	m_Circle->SetPosition(0.f, 0.f);
	m_Circle->SetColor(255.f, 0.f, 0.f);
	AddChild( m_Circle );

	m_Animation = NNAnimation::Create( 5,	L"Sprite/animation/explosion_10011.png",
											L"Sprite/animation/explosion_10012.png", 
											L"Sprite/animation/explosion_10013.png",
											L"Sprite/animation/explosion_10014.png",
											L"Sprite/animation/explosion_10015.png");

	m_Animation->SetLoop(false);
	m_Animation->SetVisible(false);
	AddChild( m_Animation );


	m_Cost = 50;
	m_Stage = FIRST_STAGE_CHAR;

	m_bHit = false;

	m_PacketHandler = new CPacketHandler;
}

CMaincharacter::~CMaincharacter(void)
{
	//핸들러를 해제
	//SafeDelete(m_PacketHandler);
}

void CMaincharacter::Render()
{
	NNObject::Render();
}

//**************************************************************
//                         Update
//**************************************************************

//송신측의 함수
void CMaincharacter::Update(float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode)
{
	m_Syntime += dTime;

	m_skill_key_input = NNInputSystem::GetInstance()->GetSkillKeyInput();
	m_direct_key_input = NNInputSystem::GetInstance()->GetDirectionKeyInput();
	m_speed_key_input = NNInputSystem::GetInstance()->GetChangeSpeedKeyInput();

	//스피드키 입력에 따른 스피드 조정
	if (m_speed_key_input == CHANGE_SPEED)
	{
		SetSpeed(CHAR_FAST_SPEED);
	}
	else
	{
		SetSpeed(CHAR_SPEED);
	}

	//항상 적을 바라보도록 계산
	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateSatellite(dTime, enemy);
	m_Texture->SetRotation(GetShotDirection());

	//이동과 스킬시전
	UpdateMotion(dTime, m_direct_key_input);
	SkillCasting(dTime, enemy, map, m_skill_key_input);

	switch (gamemode)
	{
	case TEST_MODE:
		break;
	default:
		//만약 스킬키와 이동키에 변화가 있다면 패킷전송
		if ((m_skill_key_input != NONE) || 
			(m_StateOfDirectionKey != m_direct_key_input) ||
			(m_StateOfSpeedKey != m_speed_key_input))
		{
			m_PacketHandler->m_PacketKeyStatus.mSkillStatus = (short)m_skill_key_input;
			m_PacketHandler->m_PacketKeyStatus.mDirectionStatus = (short)m_direct_key_input;
			m_PacketHandler->m_PacketKeyStatus.mSpeedStatus = (short)m_speed_key_input;
			printf_s("***********************send!************************\n");
			NNNetworkSystem::GetInstance()->Write( (const char*)&m_PacketHandler->m_PacketKeyStatus, m_PacketHandler->m_PacketKeyStatus.m_Size );

			m_StateOfDirectionKey = m_direct_key_input;
			m_StateOfSpeedKey = m_speed_key_input;
		}
		break;
	}

}

//수신받은 후 업데이트 하는 함수
void CMaincharacter::UpdateByPeer( float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode)
{
	m_Syntime += dTime;

	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateSatellite(dTime, enemy);

	m_Texture->SetRotation(GetShotDirection());

	printf_s("recv : %d\n", m_direct_key_input);

	//전송된 패킷에 변화가 있다면 상태변화 및 스킬시전
	if (m_PacketHandler->m_IsPacketrecv == true)
	{
		m_StateOfDirectionKey = (EInputSetUp)m_PacketHandler->m_PacketKeyStatus.mDirectionStatus;
		m_StateOfSkillKey = (EInputSetUp)m_PacketHandler->m_PacketKeyStatus.mSkillStatus;
		m_StateOfSpeedKey = (EInputSetUp)m_PacketHandler->m_PacketKeyStatus.mSpeedStatus;

		SkillCasting(dTime, enemy, map, m_StateOfSkillKey);

		//패킷을 꺼내읽었다고 표시
		m_PacketHandler->m_IsPacketrecv = false;
	}

	//스피드키 입력에 따른 스피드 조정
	if (m_StateOfSpeedKey == CHANGE_SPEED)
	{
		SetSpeed(CHAR_FAST_SPEED);
	}
	else
	{
		SetSpeed(CHAR_SPEED);
	}

	UpdateMotion(dTime, m_StateOfDirectionKey);
}

void CMaincharacter::UpdateMotion(float dTime, EInputSetUp move_key)
{
	//입력에 따른 캐릭터의 이동
	switch (move_key)
	{
	case UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(270), GetSpeed()*NNDegreeToY(270)) * dTime );
		break;
	case DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(90), GetSpeed()*NNDegreeToY(90)) * dTime );
		break;
	case LEFT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(180), GetSpeed()*NNDegreeToY(180)) * dTime );
		break;
	case RIGHT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(0), GetSpeed()*NNDegreeToY(0)) * dTime );
		break;
	case LEFT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(225), GetSpeed()*NNDegreeToY(225))*dTime );
		break;
	case LEFT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(135), GetSpeed()*NNDegreeToY(135)) * dTime );
		break;
	case RIGHT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(315), GetSpeed()*NNDegreeToY(315))* dTime );
		break;
	case RIGHT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(45), GetSpeed()*NNDegreeToY(45)) * dTime );
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//								 skillcasting									 //
///////////////////////////////////////////////////////////////////////////////////

void CMaincharacter::SkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key)
{
	switch (GetStage())
	{
	case FIRST_STAGE_CHAR:
		FirstStageSkillCasting(dTime, enemy, map, skill_key);
		break;
	default:
		break;
	}
}

void CMaincharacter::FirstStageSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key)
{
	switch (skill_key)
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= SHOT_BULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(this, NORMAL_BULLET);
			SetCost( GetCost() - SHOT_BULLET_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SHOT_ACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(this, ACCEL_BULLET);
			SetCost( GetCost() - SHOT_ACCELBULLET_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= SECTOR_SINGLE_COST*20 )
		{
			CBulletManager::GetInstance()->ShotSectorMixBullets(this, ACCEL_BULLET, NORMAL_BULLET);
			SetCost( GetCost() - SECTOR_SINGLE_COST*20 );
		}
		break;
	case SKILL_KEY_FOUR:
		if ( GetCost() >= TORNADO_SINGLE_COST*6 )
		{
			CBulletManager::GetInstance()->ShotTornadoBullets(this, 6);
			SetCost( GetCost() - TORNADO_SINGLE_COST*6 );
		}
		break;
	case SKILL_KEY_FIVE:
		if ( GetCost() >= SETUP_SATELLITE_COST )
		{
			SetupSatellite();
			SetCost(GetCost() - SETUP_SATELLITE_COST);
		}
		break;
	case SKILL_KEY_SIX:
		if (GetCost() >= SL_SECTORNORMAL_COST)
		{
			ShotSLSectorNormalBullet();
			SetCost(GetCost() - SL_SECTORNORMAL_COST);
		}
		break;
	}
}

//**************************************************************
//                         Satellite
//**************************************************************
void CMaincharacter::SetupSatellite()
{
	CSatellite* pSatellite = GetSatellite();
	pSatellite->SetPosition(GetPosition());
}

void CMaincharacter::UpdateSatellite(float dTime , CMaincharacter* Enemy)
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->Update(dTime, Enemy);
		}
	}
}

CSatellite * CMaincharacter::GetSatellite()
{
	++m_SatelliteIndex;
	m_SatelliteIndex %= MAX_SATELLITE_NUM;
	m_pSatelliteArray[m_SatelliteIndex]->SetVisible(true);

	return m_pSatelliteArray[m_SatelliteIndex];
}

void CMaincharacter::ShotSLSectorNormalBullet()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			CBulletManager::GetInstance()->ShotSectorBullets(m_pSatelliteArray[i], NORMAL_BULLET);
		}
	}
}

void CMaincharacter::DestroySatellite()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->SetVisible(false);
			m_pSatelliteArray[i]->InitMember();
		}
	}
}

//**************************************************************
//                         Animation
//**************************************************************
bool CMaincharacter::UpdateExplosionAnimation( float dTime )
{
	//애니메이션
	m_Animation->SetVisible(true);
	m_Animation->Update(dTime);

	//애니메이션이 끝나면 끝났다고 알려준다.
	return m_Animation->IsAnimationEnd();
}
