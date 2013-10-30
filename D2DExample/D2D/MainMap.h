#pragma once
#include "NNRect.h"

class CMainMap : public NNObject
{
public:
	CMainMap(void);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime );

	NNRect * GetMainFrame() {return m_MainFrame;}

private:
	NNRect * m_MainFrame;
};

