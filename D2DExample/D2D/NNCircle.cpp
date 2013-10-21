#include "NNCircle.h"
#include "NNResourceManager.h"
#include "NNApplication.h"

//////////////////////////////////////////////////////////////////////////
/*					NNCircle											*/
//////////////////////////////////////////////////////////////////////////
NNCircle*  NNCircle::Create()
{
	//뭘로 랜더하는지 값을 받아옴
	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();
	
	NNCircle* pInstance = nullptr;
	switch ( rendererStatus )
	{
	case D2D:
		pInstance = new NND2DCircle();
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
	m_ellipse.point;
	m_ellipse.radiusX;
	m_ellipse.radiusY;
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
	m_pD2DRenderer->GetHwndRenderTarget()->DrawEllipse();
}