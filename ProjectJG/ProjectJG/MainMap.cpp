#include "NNConfig.h"
#include "MainMap.h"

CMainMap::CMainMap(void)
{
	m_MainFrame = NNRect::Create(750.f, 750.f);
	m_MainFrame->SetPosition(0.f,0.f);
	AddChild(m_MainFrame);
}


CMainMap::~CMainMap(void)
{
}

void CMainMap::Render()
{
	NNObject::Render();
}

void CMainMap::Update( float dTime )
{

}