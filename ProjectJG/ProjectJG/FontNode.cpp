#include "NNConfig.h"
#include "GameOption.h"
#include "FontNode.h"

CFontNode::CFontNode(void)
{
	for (int i = 0; i < 100; i++)
	{
		m_Texture[i] = NNSpriteAtlas::Create( FONT_IMAGE );
		m_Texture[i]->SetCutSize(0, 0, FONT_WIDTH, FONT_HEIGHT);
		AddChild(m_Texture[i]);
		m_Texture[i]->SetPosition((float)FONT_WIDTH*i, 0.f);
	}
}


CFontNode::~CFontNode(void)
{
}
