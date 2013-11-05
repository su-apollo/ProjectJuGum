#pragma once
#include "NNRect.h"

class CMainMap : public NNObject
{
public:
	CMainMap(void);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime );
	float GetTopLine() { return GetPositionY() - m_MainFrame->GetHeight()/2; }
	float GetBotLine() { return GetPositionY() + m_MainFrame->GetHeight()/2; }
	float GetRightLine() { return GetPositionX() + m_MainFrame->GetWidth()/2; }
	float GetLeftLine() { return GetPositionX() - m_MainFrame->GetWidth()/2; }

	NNRect * GetMainFrame() { return m_MainFrame; }

private:
	NNRect *	m_MainFrame;
};

