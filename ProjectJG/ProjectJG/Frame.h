#pragma once
#include "NNObject.h"
#include "NNRect.h"

class CFrame :
	public NNObject
{
public:
	CFrame(void);
	virtual ~CFrame(void);

	virtual void Render() { NNObject::Render(); }
	virtual void Update( float dTime ) {}

	inline float GetTopLine()	{ return -GetHeight()*0.5f; }
	inline float GetBotLine()	{ return GetHeight()*0.5f; }
	inline float GetRightLine()	{ return GetWidth()*0.5f; }
	inline float GetLeftLine()	{ return -GetWidth()*0.5f; }

	NNRect *	GetMainFrame() { return m_MainFrame; }
	float		GetWidth()	{ return m_Width; }
	float		GetHeight()	{ return m_Height; }

	virtual void SetSize( float width, float height ) { m_MainFrame->SetWidth(width); m_MainFrame->SetHeight(height); }

protected:
	NNRect *	m_MainFrame;
	float		m_Width;
	float		m_Height;
};

