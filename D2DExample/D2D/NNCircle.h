#pragma once
#include "NNObject.h"
#include "NNConfig.h"

#include "NND2DRenderer.h"

class NNCircle :
	public NNObject
{

public:
	NNCircle(void)
		:m_radius(0.f), m_ColorR(0.f), m_ColorG(0.f), m_ColorB(0.f), m_Opacity(1.f) {}
	virtual ~NNCircle(void) {}

	static NNCircle* Create( float radius );
	virtual void Destroy() {}
	virtual void Render() {}

	inline float GetOpacity() const { return m_Opacity; }
	float GetRadius() {return m_radius;}

	void SetOpacity( float opacity ) { m_Opacity = opacity; }
	virtual void SetRed( float r ) { m_ColorR = r; }
	virtual void SetGreen( float g ) { m_ColorG = g; }
	virtual void SetBlue( float b ) { m_ColorB = b; }
	virtual void SetColor( float r, float g, float b ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; }


protected:
	float m_ColorR, m_ColorG, m_ColorB;
	float m_radius;
	float m_Opacity;
};

class NND2DCircle:
	public NNCircle
{
public:
	NND2DCircle(void);
	NND2DCircle( float radius );
	NND2DCircle(float radius, float startR, float startG, float startB, float endR, float endG, float endB);
	NND2DCircle(float radius, D2D1::ColorF::Enum startColor, D2D1::ColorF::Enum endColor);
	virtual ~NND2DCircle(void);

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
	D2D1_ELLIPSE	m_Ellipse;
	ID2D1SolidColorBrush * m_Brush;
	ID2D1RadialGradientBrush *m_pRadialGradientBrush;
	ID2D1GradientStopCollection *m_pGradientStops;
	D2D1_GRADIENT_STOP gradientStops[2];
	
};
