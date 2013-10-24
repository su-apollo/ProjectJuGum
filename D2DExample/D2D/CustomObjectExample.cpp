
#include "CustomObjectExample.h"


CustomObjectExample::CustomObjectExample()
{
	m_CustomObject = CustomObject::Create();
	AddChild( m_CustomObject );
}
CustomObjectExample::~CustomObjectExample()
{

}

void CustomObjectExample::Render()
{
	NNScene::Render();
}
void CustomObjectExample::Update( float dTime )
{
	m_CustomObject->Update( dTime );
}