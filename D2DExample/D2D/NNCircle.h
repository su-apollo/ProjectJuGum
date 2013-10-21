#pragma once
#include "NNObject.h"
#include "NNConfig.h"

#include "NND2DRenderer.h"

class NNCircle :
	public NNObject
{
protected:
	float m_ColorR, m_ColorG, m_ColorB;
	float m_Opacity;

public:
	NNCircle(void)
		:m_ColorR(0.f), m_ColorG(0.f), m_ColorB(0.f), m_Opacity(1.f) {}
	virtual ~NNCircle(void) {}

	static NNCircle* Create();
	virtual void Destroy() {}
	virtual void Render() {}

public:
	inline float GetOpacity() const { return m_Opacity; }

	void SetOpacity( float opacity ) { m_Opacity = opacity; }
};

class NND2DCircle:
	public NNCircle
{
private:
	NND2DRenderer * m_pD2DRenderer;
	D2D1_ELLIPSE	m_ellipse;

public:
	NND2DCircle(void);
	virtual ~NND2DCircle(void);

	void Destroy();
	void Render();
};
