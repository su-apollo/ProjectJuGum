#pragma once
#include "NNObject.h"
#include "NNConfig.h"

#include "NND2DRenderer.h"

class NNRect :
	public NNObject
{

public:
	NNRect(void)
		:m_width(0.f), m_height(0.f), m_ColorR(0.f), m_ColorG(0.f), m_ColorB(0.f), m_Opacity(1.f) {}
	virtual ~NNRect(void) {}

	static NNRect * Create( float width, float height );
	virtual void Destroy() {}
	virtual void Render() {}

	inline float GetOpacity() const { return m_Opacity; }
	float GetHeight() {return m_height;}
	float GetWidth() {return m_width;}

	void SetOpacity( float opacity ) { m_Opacity = opacity; }
	virtual void SetRed( float r ) { m_ColorR = r; }
	virtual void SetGreen( float g ) { m_ColorG = g; }
	virtual void SetBlue( float b ) { m_ColorB = b; }
	virtual void SetColor( float r, float g, float b ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; }

	void SetWidth( float width ) { m_width = width; }
	void SetHeight( float height ) { m_height = height; }

protected:
	float m_ColorR, m_ColorG, m_ColorB;
	float m_width;
	float m_height;
	float m_Opacity;
};

class NND2DRect:
	public NNRect
{
public:
	NND2DRect(void);
	NND2DRect( float width, float height );
	virtual ~NND2DRect(void);

	void Destroy();
	void Render();

	void SetRed( float r) { m_ColorR = r; m_Brush->SetColor(D2D1::ColorF(r/255.f,m_ColorG/255.f,m_ColorB/255.f)); }
	void SetGreen( float g ) { m_ColorG = g; m_Brush->SetColor(D2D1::ColorF(m_ColorR/255.f,g/255.f,m_ColorB/255.f)); }
	void SetBlue( float b ) { m_ColorB = b; m_Brush->SetColor(D2D1::ColorF(m_ColorR/255.f,m_ColorG/255.f,b/255.f)); }
	void SetColor( float r, float g, float b )
	{
		m_ColorR = r; m_ColorG = g; m_ColorB = b;
		m_Brush->SetColor(D2D1::ColorF(r/255.f,g/255.f,b/255.f));
	}


private:
	NND2DRenderer * m_pD2DRenderer;
	D2D1_RECT_F		m_Rect;
	ID2D1SolidColorBrush * m_Brush;

};
