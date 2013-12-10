#pragma once
#include "NNObject.h"
#include "NNSpriteAtlas.h"

class CFontNode :
	public NNObject
{
public:
	CFontNode(void);
	virtual ~CFontNode(void);

	void Render(){ NNObject::Render(); }
	void Update( float dTime ){}

	// {return m_Texutre;} 가 안 되나??
	void ChangeLetter(int index, int AtlasImageIndex){ m_Texture[index]->SetImageIndex(AtlasImageIndex); }

private:
	NNSpriteAtlas*	m_Texture[100];
	int				m_Index;
};

