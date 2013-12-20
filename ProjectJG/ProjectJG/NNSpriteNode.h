#pragma once

#include "NNSprite.h"

class NNSpriteNode : public NNObject
{
public:
	NNSpriteNode();
	virtual ~NNSpriteNode();

	void Render();
	void Update( float dTime );
	void SetImageWidth( float width ) { m_ImageWidth = width; }
	void SetImageHeight( float height ) { m_ImageHeight = height; }

	void SetOpacity( float opacity ) { m_Opacity = opacity; }

	//NNCREATE_FUNC(NNSpriteNode);

	static NNSpriteNode* Create( wchar_t* path );

public:
	NNSprite* GetSprite() const { return m_Sprite; }
	float GetFrameTime() const { return m_FrameTime; }

	void SetFrameTime( float frameTime ) { m_FrameTime = frameTime; }

private:
	NNSprite* m_Sprite;
	float m_FrameTime;

	float m_ImageWidth;
	float m_ImageHeight;

	float m_Opacity;
};