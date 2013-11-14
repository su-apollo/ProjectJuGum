#include "NNConfig.h"
#include "NNRect.h"
#include "NNResourceManager.h"
#include "NNApplication.h"

//////////////////////////////////////////////////////////////////////////
/*					NNRect   											*/
//////////////////////////////////////////////////////////////////////////
NNRect*  NNRect::Create( float width, float height)
{
	//뭘로 랜더하는지 값을 받아옴
	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();

	NNRect* pInstance = nullptr;
	switch ( rendererStatus )
	{
	case D2D:
		pInstance = new NND2DRect( width, height );
		break;
	default:
		break;
	}

	return pInstance;
}

//////////////////////////////////////////////////////////////////////////
/*					NND2DRect											*/
//////////////////////////////////////////////////////////////////////////
NND2DRect::NND2DRect()
	: m_pD2DRenderer(nullptr), m_Brush(nullptr)
{
}

NND2DRect::NND2DRect( float width, float height )
{
	m_width = width;
	m_height = height;
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());
	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(m_ColorR, m_ColorG, m_ColorB), &m_Brush);

	m_Rect.bottom = -width/2;
	m_Rect.left = -height/2;
	m_Rect.right = width/2;
	m_Rect.top = height/2;
}

NND2DRect::~NND2DRect()
{
	Destroy();
}

void NND2DRect::Destroy()
{
	m_pD2DRenderer = nullptr;
}

void NND2DRect::Render()
{
	NNObject::Render();

	m_pD2DRenderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_pD2DRenderer->GetHwndRenderTarget()->DrawRectangle(m_Rect, m_Brush);
}