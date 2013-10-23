#include "Player.h"

CPlayer::CPlayer(void)
{
	m_Circle = NNCircle::Create(40.f);
	m_Circle->SetPosition(0.f, 100.f);
	AddChild( m_Circle );
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Render()
{
	NNObject::Render();
}

void CPlayer::Update( float dTime )
{

}