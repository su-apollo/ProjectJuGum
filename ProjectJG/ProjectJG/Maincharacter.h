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
	//임시로 만든 함수
	void			Update(float dTime, CMaincharacter* enemy, CMainMap* map);
	
	void			Update(float dTime, CMaincharacter* enemy, CMainMap* map, int framenum);
	void			UpdateByPeer(float dTime, CMaincharacter* enemy, CMainMap* map, int framenum);

	void			UpdateMotion(float dTime, EInputSetUp skill_key, EInputSetUp move_key);
	void			FirstStageSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key);

	NNCircle *		GetMainCircle(){return m_Circle;}

	float			GetCost() {return m_Cost;}
	ECharcterStage  GetStage() {return m_Stage;}

	void			SetCost(float cost) {m_Cost = cost;}
	void			SetStage(ECharcterStage new_stage) {m_Stage = new_stage;}
	void			SkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key);

	void			SetbHit( bool bHit ) { m_bHit = bHit; }
	bool			GetbHit() { return m_bHit; }

protected:
	NNSpriteAtlas*	m_Texture;
	NNCircle*		m_Circle;
	ECharcterStage  m_Stage;
	float			m_Cost;

	bool			m_bHit;
};

