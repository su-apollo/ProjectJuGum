#pragma once
#include "NNScene.h"

class NNLabel;

// agebreak : 클래스 이름 위에, 무슨 클래스인지 간략한 설명을 주석으로 달아놓을것!
class CReturnScene :
	public NNScene
{
public:
	CReturnScene(void);
	virtual ~CReturnScene(void);

	void Render();
	void Update( float dTime );

private:
	NNLabel* m_ReturnLabel;
	NNLabel* m_YesLabel;
	NNLabel* m_NoLabel;

	bool m_bReturn;
};

