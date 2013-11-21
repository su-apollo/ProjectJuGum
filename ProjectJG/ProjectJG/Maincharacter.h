#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"
#include "NNPoint.h"

class NNCircle;
class CMainMap;
class NNSpriteAtlas;

//메인케릭터 펙토리형태로 구성
class CMaincharacter : public CGameMoveObj
{
public:
	CMaincharacter(void);
	virtual ~CMaincharacter(void);

	void			Render();
	void			Update(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);
	void			Update_NetworkMode(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map, int framenum);
	void			UpdateEnemyMotion_NetworkMode(float dTime, int framenum);

	NNCircle *		GetMainCircle(){return m_Circle;}

	float			GetCost() {return m_Cost;}
	ECharcterStage  GetStage() {return m_Stage;}

	void			SetCost(float cost) {m_Cost = cost;}
	void			SetStage(ECharcterStage new_stage) {m_Stage = new_stage;}
	void			SkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);

protected:
	NNSpriteAtlas*	m_Texture;
	NNCircle*		m_Circle;
	ECharcterStage  m_Stage;
	float			m_Cost;

	void			UpdateMotion(float dTime);
	void			FirstStageSkillCasting(float dTime , CMaincharacter* player, CMaincharacter* enemy, CMainMap* map);
};

