#include "NNConfig.h"
#include "NNSpriteAtlas.h"
#include "NNResourceManager.h"
#include "NNApplication.h"

//////////////////////////////////////////////////////////////////////////
/*					NNSpriteAtlas										*/
//////////////////////////////////////////////////////////////////////////
NNSpriteAtlas* NNSpriteAtlas::Create( std::wstring path )
{
	static RendererStatus rendererStatus = NNApplication::GetInstance()->GetRendererStatus();

	NNSpriteAtlas* pInstance = nullptr;
	/*switch ( rendererStatus )
	{
	case D2D:
	*/	pInstance = new NND2DSpriteAtlas( path );
	/*	break;
	default:
		break;
	}*/
	
	return pInstance;
}

//////////////////////////////////////////////////////////////////////////
/*					NND2DSpriteAtlas									*/
//////////////////////////////////////////////////////////////////////////
NND2DSpriteAtlas::NND2DSpriteAtlas()
	: m_pD2DRenderer(nullptr), m_pD2DTexture(nullptr)
{

}
NND2DSpriteAtlas::NND2DSpriteAtlas( std::wstring path )
{
	m_pD2DRenderer = static_cast<NND2DRenderer*>(NNApplication::GetInstance()->GetRenderer());
	m_pD2DTexture = static_cast<NND2DTexture*>(NNResourceManager::GetInstance()->LoadTextureFromFile( path ));

	m_ImageWidth = m_pD2DTexture->GetD2DBitmap()->GetSize().width;
	m_ImageHeight = m_pD2DTexture->GetD2DBitmap()->GetSize().height;

	m_CutLeftX = 0;
	m_CutRightX = m_ImageWidth;
	m_CutTopY = 0;
	m_CutBottomY = m_ImageHeight;

	m_CutImageWidth = m_CutRightX - m_CutLeftX;
	m_CutImageHeight = m_CutBottomY - m_CutTopY;
}
NND2DSpriteAtlas::~NND2DSpriteAtlas()
{
	Destroy();
}
void NND2DSpriteAtlas::Destroy()
{
	m_pD2DRenderer = nullptr;
	m_pD2DTexture = nullptr;
}

void NND2DSpriteAtlas::Render()
{
	NNObject::Render();

	m_pD2DRenderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_pD2DRenderer->GetHwndRenderTarget()->DrawBitmap( 
		m_pD2DTexture->GetD2DBitmap(), D2D1::RectF(-m_CutImageWidth*0.5f,-m_CutImageHeight*0.5f,m_CutImageWidth*0.5f,m_CutImageHeight*0.5f),
		m_Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF( m_CutImageWidth*m_ColIdx + m_CutLeftX, m_CutImageHeight*m_RowIdx + m_CutTopY, m_CutImageWidth*m_ColIdx + m_CutRightX, m_CutImageHeight*m_RowIdx + m_CutBottomY ) );
}

