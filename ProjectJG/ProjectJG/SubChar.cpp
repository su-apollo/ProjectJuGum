#include "NNConfig.h"
#include "SubChar.h"
#include "NNAnimation.h"

CSubChar::CSubChar(ESubCharType type_of_char)
{
	if ( type_of_char == YUKARI )
	{
		m_FlyMotion = NNAnimation::Create( 4, 0.2f,	
			L"Sprite/SubCharR1.png",
			L"Sprite/SubCharR2.png",
			L"Sprite/SubCharR3.png",
			L"Sprite/SubCharR4.png");
	}
	else if ( type_of_char == ALICE )
	{
		m_FlyMotion = NNAnimation::Create( 4, 0.2f,	
			L"Sprite/SubCharB1.png",
			L"Sprite/SubCharB2.png",
			L"Sprite/SubCharB3.png",
			L"Sprite/SubCharB4.png");
	}

	m_FlyMotion->SetScale(1.5f, 1.5f);
	AddChild( m_FlyMotion );

	m_Type = type_of_char;
}


CSubChar::~CSubChar(void)
{
}

void CSubChar::Render()
{
	NNObject::Render();
}

void CSubChar::Update( float dTime, CMaincharacter* Enemy )
{
	m_FlyMotion->Update(dTime);
}
