
#include "CustomObject.h"
#include "NNInputSystem.h"
#include "NNApplication.h"
#define _USE_MATH_DEFINES
#include <math.h>


CustomObject::CustomObject()
{
	m_Sprite = NNSprite::Create( L"Sprite/CustomObjectExmaple/sprite.png" );
	m_Sprite->SetPosition( 0.f, 40.f );
	AddChild( m_Sprite );

	m_Label = NNLabel::Create( L"우리는 한 몸!", L"궁서체", 40.f );
	AddChild( m_Label );

	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 100.f);
	AddChild( m_Circle );

	m_Speed = 500.f;
}
CustomObject::~CustomObject()
{

}

void CustomObject::Render()
{
	NNObject::Render();
}
void CustomObject::Update( float dTime )
{
	// 원래 하려고 했던 방법
	// 창 범위 벗어나지 않게 하는 것도 한꺼번에 가능........... 여기서 처리 할 필요없나? 필요없으면 if 지워주면 됨.
	float x=0, y=0;
	NNApplication* Application = NNApplication::GetInstance();

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_PRESSED )
	{
		if (GetPositionX() > 0) x -= m_Speed;
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_PRESSED )
	{
		if (GetPositionX() < Application->GetScreenWidth()) x += m_Speed;
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_PRESSED )
	{
		if (GetPositionY() > 0) y -= m_Speed;
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_PRESSED )
	{
		if (GetPositionY() < Application->GetScreenHeight()) y += m_Speed;
	}

	if ( x * y != 0 )
	{
		SetPosition( GetPosition() + NNPoint(x, y) * dTime / sqrt(pow(x, 2) + pow(y, 2)) * m_Speed );
	}
	else
	{
		SetPosition( GetPosition() + NNPoint(x, y) * dTime );
	}
}