#include "Satellite.h"
#include "NNCircle.h"

CSatellite::CSatellite(void)
{
	m_Circle = NNCircle::Create(20.f);
	m_Circle->SetPosition(0.f, 0.f);
	AddChild( m_Circle );
}


CSatellite::~CSatellite(void)
{
}

void CSatellite::Update( float dTime )
{
}
 
void CSatellite::Render()
{
	NNObject::Render();
}


