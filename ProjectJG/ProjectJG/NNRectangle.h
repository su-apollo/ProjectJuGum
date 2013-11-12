#pragma once
#include "NNObject.h"
#include "NNConfig.h"

#include "NND2DRenderer.h"

class NNRectangle :
	public NNObject
{
protected:
	float m_ColorR, m_ColorG, m_ColorB;
 	float m_width;
 	float m_height;
	float m_Opacity;

public:
	NNRectangle(void)
		:m_height(0.f), m_width(0.f), m_ColorR(0.f), m_ColorG(0.f), m_ColorB(0.f), m_Opacity(1.f) {}
	virtual ~NNRectangle(void);

	static NNRectangle* Create(float width, float height );
	virtual void Destroy() {}
	virtual void Render() {}
	
	inline float GetOpacity() const{return m_Opacity;}
	
	void setOpacity (float opacity){m_Opacity = opacity;}
	virtual void SetRed(float red){m_ColorR = red;}
	virtual void SetGreen(float green) {m_ColorG = green;}
	virtual void SetBlue(float blue){m_ColorB = blue;}
	virtual void SetColor (float red, float green, float blue){
		SetRed(red); 
		SetBlue(blue); 
		SetGreen(green); 
	}
};

class NND2DRectangle: public NNRectangle
{
public:
	NND2DRectangle(void);
	NND2DRectangle(float width, float height);
	virtual ~NND2DRectangle(void);

	void Destroy();
	void Render();

//이하 컬러 부분 복붙했음
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
	D2D1_RECT_F m_Rectangle;
	ID2D1SolidColorBrush * m_Brush;
};

