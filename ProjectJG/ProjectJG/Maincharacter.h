#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"

class NNCircle;
class CMainMap;

//메인케릭터 펙토리형태로 구성
class CMaincharacter : public CGameMoveObj
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void			Render();
	void			Update(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);

	NNCircle *		GetMainCircle(){return m_Circle;}

	float			GetCost() {return m_Cost;}
	ECharcterStage  GetStage() {return m_Stage;}

	void			SetCost(float cost) {m_Cost = cost;}
	void			SetStage(ECharcterStage new_stage) {m_Stage = new_stage;}
	void			SkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);

protected:
	NNCircle*		m_Circle;
	ECharcterStage  m_Stage;
	float			m_Cost;

	void			UpdateMotion(float dTime);
	void			FirstStageSkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);
};

