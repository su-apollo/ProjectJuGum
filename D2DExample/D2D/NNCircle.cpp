#include "NNCircle.h"
#include "NNResourceManager.h"
#include "NNApplication.h"

//////////////////////////////////////////////////////////////////////////
/*					NNCircle											*/
//////////////////////////////////////////////////////////////////////////
NNCircle*  NNCircle::Create( float radius )
{
	//뭘로 랜더하는지 값을 받아옴
	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();
	
	NNCircle* pInstance = nullptr;
	switch ( rendererStatus )
	{
	case D2D:
		pInstance = new NND2DCircle( radius );
		break;
	default:
		break;
	}

	return pInstance;
}

//////////////////////////////////////////////////////////////////////////
/*					NND2DCircle											*/
//////////////////////////////////////////////////////////////////////////
NND2DCircle::NND2DCircle()
	: m_pD2DRenderer(nullptr), m_Brush(nullptr), m_pRadialGradientBrush(nullptr), m_pGradientStops(nullptr)
{
}

NND2DCircle::NND2DCircle( float radius)
{

	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	gradientStops[1].position = 1.0f;



	m_radius = radius;
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());


	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(m_ColorR, m_ColorG, m_ColorB), &m_Brush);
	
	m_pD2DRenderer->GetHwndRenderTarget()->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);

	m_pD2DRenderer->GetHwndRenderTarget()->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(75,75), D2D1::Point2F(0,0),75,75), m_pGradientStops, &m_pRadialGradientBrush);
	


	m_Ellipse.point.x = 0.f;
	m_Ellipse.point.y = 0.f;
	m_Ellipse.radiusX = radius;
	m_Ellipse.radiusY = radius;
}

NND2DCircle::~NND2DCircle()
{
	Destroy();
}

void NND2DCircle::Destroy()
{
	m_pD2DRenderer = nullptr;
}

void NND2DCircle::Render()
{
	NNObject::Render();

	m_pD2DRenderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_pD2DRenderer->GetHwndRenderTarget()->DrawEllipse(m_Ellipse, m_Brush);

	m_pD2DRenderer->GetHwndRenderTarget()->FillEllipse(m_Ellipse, m_pRadialGradientBrush);
}