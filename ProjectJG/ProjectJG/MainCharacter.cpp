#include "NNConfig.h"
#include "NNNetworkSystem.h"
#include "NNApplication.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "NNInputSystem.h"
#include "NNCircle.h"
#include "NNSpriteAtlas.h"
#include "Fairy.h"
#include "PacketHandler.h"
#include "NNAnimation.h"
#include "Bullet.h"
#include "SubChar.h"

CMaincharacter::CMaincharacter(ECharcterType type_of_char) 
	: m_bHit(false), m_FairyIndex(0), m_Syntime(0.f)
{
	SetHitRadius(CHAR_HIT_RADIUS);
	
// 	m_Circle = NNCircle::Create(GetHitRadius());
// 	m_Circle->SetPosition(0.f, 0.f);
// 	m_Circle->SetColor(255.f, 0.f, 0.f);
// 	AddChild( m_Circle );

	if ( type_of_char == RAYMU )
	{
		m_FlyMotion = NNAnimation::Create( 8, 0.2f,	
			L"Sprite/CharR1.png",
			L"Sprite/CharR2.png",
			L"Sprite/CharR3.png",
			L"Sprite/CharR4.png",
			L"Sprite/CharR5.png",
			L"Sprite/CharR6.png",
			L"Sprite/CharR7.png",
			L"Sprite/CharR8.png");
	}
	else if ( type_of_char == MARISA )
	{
		m_FlyMotion = NNAnimation::Create( 8, 0.2f,	
			L"Sprite/CharB1.png",
			L"Sprite/CharB2.png",
			L"Sprite/CharB3.png",
			L"Sprite/CharB4.png",
			L"Sprite/CharB5.png",
			L"Sprite/CharB6.png",
			L"Sprite/CharB7.png",
			L"Sprite/CharB8.png");
	}
	
	m_FlyMotion->SetScale(1.5f, 1.5f);
	AddChild( m_FlyMotion );

	m_Type = type_of_char;
	m_Cost = 50;
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
		SetSpeed(CHAR_SLOW_SPEED);
	}
	else
	{
		SetSpeed(CHAR_SPEED);
	}

	//항상 적을 바라보도록 계산
	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateFairy(dTime, enemy);

	m_FlyMotion->Update(dTime);
	m_FlyMotion->SetRotation(GetShotDirection() + 90.f);
	

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
	UpdateFairy(dTime, enemy);

	m_FlyMotion->Update(dTime);
	m_FlyMotion->SetRotation(GetShotDirection() + 90.f);

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
		SetSpeed(CHAR_SLOW_SPEED);
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
	switch (GetType())
	{
	case RAYMU:
	case MARISA:
		RaymuSkillCasting(dTime, enemy, map, skill_key);
		break;
	default:
		break;
	}
}

//스킬을 사용할 수 있는지 코스트를 확인 사용후 코스트를 소모
void CMaincharacter::RaymuSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key)
{
	switch (skill_key)
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= RAYMU_NORMAL_ATTACK_COST )
		{
			RaymuNomalShot();
			SetCost( GetCost() - RAYMU_NORMAL_ATTACK_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SUMMON_FAIRY_COST )
		{
			SummonFairy();
			SetCost( GetCost() - SUMMON_FAIRY_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= FAIRY_SKILL_1_COST  )
		{
			FairySkill_1();
			SetCost( GetCost() - FAIRY_SKILL_1_COST  );
		}
		break;
	case SKILL_KEY_FOUR:
		break;
	case SKILL_KEY_FIVE:
		break;
	case SKILL_KEY_SIX:
		break;
	}
}

//**************************************************************
//                         Skills
//**************************************************************

void CMaincharacter::RaymuNomalShot()
{
	CBullet * pBullet = CBulletManager::GetInstance()->GetBullet(RAYMU_NORMAL_BULLET, GetSpeed(), GetShotDirection());
	pBullet->SetDirection(GetShotDirection());
	pBullet->SetPosition(GetShotPoint());
}

void CMaincharacter::FairySkill_1()
{
	for (int i = 0; i < MAX_FAIRY_NUM; ++i)
	{
		if (m_pFairyArray[i]->IsVisible())
		{
			for ( int j = 0; j < 6; ++j )
			{
				float direction = m_pFairyArray[i]->GetShotDirection() - 120*0.5f + 120/5*j ;

			 	CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(FAIRY_NORMAL_BULLET, 0, direction);
			 	pBullet->SetPosition(m_pFairyArray[i]->GetShotPoint());
			 	pBullet->SetDirection(direction);
			}
		}
	}
}

//**************************************************************
//						   Fairy
//**************************************************************
void CMaincharacter::SummonFairy()
{
	CFairy* pFairy = GetFairy();
	pFairy->SetPosition(GetPosition());
}

void CMaincharacter::UpdateFairy(float dTime , CMaincharacter* Enemy)
{
	for (int i = 0; i < MAX_FAIRY_NUM; ++i)
	{
		if (m_pFairyArray[i]->IsVisible())
		{
			m_pFairyArray[i]->Update(dTime, Enemy);
		}
	}
}

CFairy * CMaincharacter::GetFairy()
{
	++m_FairyIndex;
	m_FairyIndex %= MAX_FAIRY_NUM;
	CFairy* new_Fairy = m_pFairyArray[m_FairyIndex];
	new_Fairy->SetVisible(true);

	return m_pFairyArray[m_FairyIndex];
}

void CMaincharacter::DestroyFairy()
{
	for (int i = 0; i < MAX_FAIRY_NUM; ++i)
	{
		if (m_pFairyArray[i]->IsVisible())
		{
			m_pFairyArray[i]->SetVisible(false);
			m_pFairyArray[i]->InitMember();
		}
	}
}

//**************************************************************
//                         Animation
//**************************************************************
bool CMaincharacter::UpdateExplosionAnimation( float dTime )
{
	//죽는모션(추가예정)
	return true;
}




