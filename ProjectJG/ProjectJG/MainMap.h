#pragma once
#include "NNRect.h"

class CMainMap : public NNObject
{
public:
	CMainMap(void);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime );
	inline float GetTopLine() { return GetPositionY() - m_MainFrame->GetHeight()*0.5f; }
	inline float GetBotLine() { return GetPositionY() + m_MainFrame->GetHeight()*0.5f; }
	inline float GetRightLine() { return GetPositionX() + m_MainFrame->GetWidth()*0.5f; }
	inline float GetLeftLine() { return GetPositionX() - m_MainFrame->GetWidth()*0.5f; }

	NNRect * GetMainFrame() { return m_MainFrame; }

private:
	NNRect *	m_MainFrame;
};

