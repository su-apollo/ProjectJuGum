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

	inline float GetTopLine()	{ return -m_Height*0.5f; }
	inline float GetBotLine()	{ return m_Height*0.5f; }
	inline float GetRightLine()	{ return m_Width*0.5f; }
	inline float GetLeftLine()	{ return -m_Width*0.5f; }

	float		GetWidth()	{ return m_Width; }
	float		GetHeight()	{ return m_Height; }

	virtual void SetSize( float width, float height )
	{ 
		m_Width = width; m_Height = height;
	}

protected:
	float		m_Width;
	float		m_Height;
};

