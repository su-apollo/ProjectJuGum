#include "NNConfig.h"
#include "MainMap.h"
#include "GameOption.h"

CMainMap::CMainMap(void)
{
	m_Width = MAIN_MAP_WIDTH;
	m_Height = MAIN_MAP_HEIGHT;

	m_MainFrame = NNRect::Create(m_Width, m_Height);
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