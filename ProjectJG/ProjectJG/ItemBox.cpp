#include "NNConfig.h"
#include "ItemBox.h"
#include "NNAnimation.h"

CItemBox::CItemBox(void)
{
	m_FlyMotion = NNAnimation::Create( 8, 0.2f,	
		L"Sprite/ib1.png",
		L"Sprite/ib2.png",
		L"Sprite/ib3.png",
		L"Sprite/ib4.png",
		L"Sprite/ib5.png",
		L"Sprite/ib6.png",
		L"Sprite/ib7.png",
		L"Sprite/ib8.png");
}

CItemBox::~CItemBox(void)
{
}

void CItemBox::Render()
{
	NNObject::Render();
}

void CItemBox::Update( float dTime )
{
	m_FlyMotion->Update(dTime);

	float x = GetSpeed() * NNDegreeToX(GetDirection());
	float y = GetSpeed() * NNDegreeToY(GetDirection());

	SetPosition(GetPositionX()+x*dTime, GetPositionY()+y*dTime);
}
