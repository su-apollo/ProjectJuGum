#pragma once
#include "NNScene.h"

class NNLabel;

// 메인 메뉴로 돌아갈건지 묻는 씬 (+pause기능) 이었는데 ... 안 씀 ㅋㅋ

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

