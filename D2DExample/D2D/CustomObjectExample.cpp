
#include "CustomObjectExample.h"
#include "NNApplication.h"


CustomObjectExample::CustomObjectExample()
{
	m_CustomObject = CustomObject::Create();
	AddChild( m_CustomObject );

	m_SumTime = 0;
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
	// FPS
	m_SumTime += dTime;
	if ( m_SumTime > 0.2 )
	{
		printf_s("FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
		m_SumTime = 0;
	}
	m_CustomObject->Update( dTime );
}