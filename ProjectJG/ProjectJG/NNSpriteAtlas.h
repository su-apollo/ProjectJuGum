
#pragma once

#include "NNObject.h"
#include "NNConfig.h"

#include "NNTexture.h"
#include "NND2DRenderer.h"

class NNSpriteAtlas : public NNObject
{
public:
	NNSpriteAtlas()
		: m_ImageWidth(0.f), m_ImageHeight(0.f), m_CutImageWidth(0.f), m_CutImageHeight(0.f),
		m_ImageIndex(0), m_RowIdx(0), m_ColIdx(0),
		m_ColorR(0.f), m_ColorG(0.f), m_ColorB(0.f), m_Opacity(1.f){}
	virtual ~NNSpriteAtlas(){}

	void Render(){}
	void Update( float dTime ){}

	static NNSpriteAtlas* Create( std::wstring path );

	inline float GetImageWidth() const { return m_ImageWidth; }
	inline float GetImageHeight() const { return m_ImageHeight; }
	inline float GetOpacity() const { return m_Opacity; }
	inline float GetCutImageWidth() const { return m_CutImageWidth;}
	inline float GetCutImageHeight() const { return m_CutImageHeight; }

	void SetOpacity( float opacity ) { m_Opacity = opacity; }
	void SetCutSize( float leftX, float topY, float rightX, float bottomY )
	{ 
		m_CutLeftX=leftX; m_CutTopY=topY; m_CutRightX=rightX; m_CutBottomY=bottomY;
		m_CutImageWidth = m_CutRightX - m_CutLeftX;
		m_CutImageHeight = m_CutBottomY - m_CutTopY;
	}

	int GetImageIndex() { return m_ImageIndex; }
	void SetImageIndex( int n )
	{
		int count = (int)(m_ImageWidth/m_CutImageWidth);
		m_ImageIndex = n; m_RowIdx = n / count; m_ColIdx = n - m_RowIdx*count;
	}
	void SetImageNext() { SetImageIndex( GetImageIndex() +1 ); }

protected:
	float m_ImageWidth;
	float m_ImageHeight;
	float m_CutImageWidth;
	float m_CutImageHeight;
	float m_ColorR, m_ColorG, m_ColorB;
	float m_Opacity;
	float m_CutLeftX, m_CutTopY, m_CutRightX, m_CutBottomY;

	int	m_ImageIndex;
	int m_RowIdx;
	int m_ColIdx;
};

class NND2DSpriteAtlas : public NNSpriteAtlas
{
private:
	NND2DRenderer* m_pD2DRenderer;
	NND2DTexture* m_pD2DTexture;

public:
	NND2DSpriteAtlas();
	NND2DSpriteAtlas( std::wstring path );
	virtual ~NND2DSpriteAtlas();

	void Destroy();
	void Render();
};