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
	: m_pD2DRenderer(nullptr)
{
}

NND2DCircle::NND2DCircle( float radius)
{
	m_radius = radius;
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());

	m_ellipse.point.x = 0.f;
	m_ellipse.point.y = 0.f;
	m_ellipse.radiusX = radius;
	m_ellipse.radiusY = radius;
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
	//임시브러쉬
	ID2D1SolidColorBrush * brush = NULL;
	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush);

	NNObject::Render();

	m_pD2DRenderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_pD2DRenderer->GetHwndRenderTarget()->DrawEllipse(m_ellipse, brush);
}