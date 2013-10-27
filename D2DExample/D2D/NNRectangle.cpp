#include "NNRectangle.h"
#include "NNResourceManager.h"
#include "NNApplication.h"

/*				NNRectangle				*/

NNRectangle* NNRectangle::Create(float width, float height )
{
	static	RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();

	NNRectangle* pInstance = nullptr;
	switch (rendererStatus)
	{
	case D2D:
		pInstance = new NND2DRectangle(width, height);
		break;
	default: 
		break;
	}

	return pInstance;
}


/*			NND2DRectangle				*/


NND2DRectangle::NND2DRectangle() 
	: m_pD2DRenderer(nullptr)	, m_Brush(nullptr){}

NND2DRectangle::NND2DRectangle(float width, float height)
{
	m_height = height;
	m_width = width;
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());
	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(m_ColorR, m_ColorG, m_ColorB), &m_Brush);

	m_Rectangle.top = 0.f;
	m_Rectangle.left = 0.f;
	m_Rectangle.bottom = height;
	m_Rectangle.right = width;
}

NND2DRectangle::~NND2DRectangle(){
	Destroy();
}

void NND2DRectangle::Destroy(){
	m_pD2DRenderer = nullptr;
}

void NND2DRectangle::Render(){
	NNObject::Render();

	m_pD2DRenderer->GetHwndRenderTarget()->SetTransform(m_Matrix);
	m_pD2DRenderer->GetHwndRenderTarget()->DrawRectangle(m_Rectangle, m_Brush);
}