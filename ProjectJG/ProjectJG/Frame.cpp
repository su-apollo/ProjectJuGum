#include "NNConfig.h"
#include "Frame.h"


CFrame::CFrame(void)
{
	m_MainFrame = NNRect::Create(0.f, 0.f);
	m_MainFrame->SetColor( 255.f, 255.f, 255.f );
	AddChild(m_MainFrame);
}


CFrame::~CFrame(void)
{
}
