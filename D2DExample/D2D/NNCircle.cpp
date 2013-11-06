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

NNCircle*  NNCircle::Create(float radius, float startR, float startG, float startB, float endR, float endG, float endB )
{
	//rgb값 입력으로 그라데이션 채색된 원 만들기
	//startR, startG, startB로 시작점 RGB값을 정하고 endR, endG, endB로 종료점 RGB값을 정함

	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();

	NNCircle* pInstance = nullptr;
	switch ( rendererStatus )
	{
	case D2D:
		pInstance = new NND2DCircle(radius, startR, startG, startB, endR, endG, endB);
		break;
	default:
		break;
	}

	return pInstance;
}

NNCircle*  NNCircle::Create(float radius, D2D1::ColorF::Enum startColor, D2D1::ColorF::Enum endColor)
{
	//D2D1::ColorF에 지정되어 있는 컬러 값으로 그라데이션 채색된 원 만들기
	//startColor가 시작점 색, endColor가 종료점 색
	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();

	NNCircle* pInstance = nullptr;
	switch ( rendererStatus )
	{
	case D2D:
		pInstance = new NND2DCircle(radius, startColor, endColor);
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

void NND2DCircle::DrawCircle(float radius)
{
	m_radius = radius;
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());

	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(m_ColorR, m_ColorG, m_ColorB), &m_Brush);

	m_Ellipse.point.x = 0.f;
	m_Ellipse.point.y = 0.f;
	m_Ellipse.radiusX = radius;
	m_Ellipse.radiusY = radius;
}

NND2DCircle::NND2DCircle( float radius)
{
	DrawCircle(radius);
}

NND2DCircle::NND2DCircle(float radius, D2D1::ColorF::Enum startColor, D2D1::ColorF::Enum endColor){
	DrawCircle(radius);

	gradientStops[0].color = D2D1::ColorF(startColor, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(endColor, 1);
	gradientStops[1].position = 1.0f;

	m_pD2DRenderer->GetHwndRenderTarget()->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);	

	m_pD2DRenderer->GetHwndRenderTarget()->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(0,0), D2D1::Point2F(0,0),radius,radius), m_pGradientStops, &m_pRadialGradientBrush);
}


NND2DCircle::NND2DCircle(float radius, float startR, float startG, float startB, float endR, float endG, float endB)
{
	DrawCircle(radius);

	gradientStops[0].color = D2D1::ColorF(startR, startG, startB, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(endR, endG, endB, 1);
	gradientStops[1].position = 1.0f;

	m_pD2DRenderer->GetHwndRenderTarget()->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);	

	m_pD2DRenderer->GetHwndRenderTarget()->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(0,0), D2D1::Point2F(0,0),radius,radius), m_pGradientStops, &m_pRadialGradientBrush);
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
	if (m_pRadialGradientBrush != nullptr)
	{
		m_pD2DRenderer->GetHwndRenderTarget()->FillEllipse(m_Ellipse, m_pRadialGradientBrush);
	}
}