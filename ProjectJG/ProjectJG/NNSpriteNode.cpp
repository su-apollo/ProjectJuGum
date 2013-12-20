#include "NNConfig.h"
#include "NNSpriteNode.h"

NNSpriteNode::NNSpriteNode()
	: m_Sprite(nullptr), m_FrameTime(0.f),
	m_ImageHeight(0.f), m_ImageWidth(0.f),
	m_Opacity(1.f)
{
}
NNSpriteNode::~NNSpriteNode()
{
}

NNSpriteNode* NNSpriteNode::Create( wchar_t* path )
{
	NNSpriteNode* pInstance = new NNSpriteNode();
	NNSprite* spriteInstance = NNSprite::Create( path );
	pInstance->m_Sprite = spriteInstance;

	pInstance->AddChild( spriteInstance );

	return pInstance;
}

void NNSpriteNode::Render()
{
	m_Sprite->SetImageHeight(m_ImageHeight);
	m_Sprite->SetImageWidth(m_ImageWidth);
	m_Sprite->SetOpacity(m_Opacity);

	NNObject::Render();
}
void NNSpriteNode::Update( float dTime )
{
	NNObject::Update( dTime );
}