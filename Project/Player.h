#pragma once

#include		"Mof.h"
#include		"GamePad.h"
#include		"EffectManager.h"
#include		"SoundManager.h"
#include		"Enemy.h"
#include		"Object.h"
#include		"Coordinate.h"
#include		"Substance.h"
#include		<vector>
#include		<list>
#include		<any>
using namespace std;


class CPlayer {



private:

	CTexture			m_Texture;
	CTexture			m_HpTexture;
	CCircle				m_SkillCircle;

	/*vector<CSubstance*>	m_SkillTarget;*/
	
	bool				m_bTrigger;
	bool				m_bJump;
	bool				m_bPowerUp;

	int					m_Life;
	int					m_Hp;
	int					m_Target;
	float				m_Skillrang;
	float				m_PosX;
	float				m_PosY;

	float				m_MoveX;
	float				m_MoveY;

	float				m_MoveX2;
	float				m_MoveY2;


public:
			CPlayer();
			~CPlayer();
	bool	Load(void);
	void	Initialize(void);
	void	Update(void);
	void	Render(Vector2 scroll);
	void	Release(void);

	void	RenderDebug(void);
	void	RenderState(void);
	void	Operation(void);
	void	PadOperation(void);
	void	KeyOperation(void);
	void	TestPadOperation(void);
	void	TestKeyOperation(void);
	void	LifeDecrease(void);
	void	Skill(void);
	void	SkillColision(CEnemy* pene, int eneCount,CObject* pobj,int objCount);
	void	   CollisionStage(Vector2 o);
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + 60, m_PosY + 64); }
	CCircle	GetCircle(void) { return m_SkillCircle; }
	Vector2 GetPos() { return Vector2(m_PosX, m_PosY); }
	Vector2 GetMove() { return Vector2(m_MoveX, m_MoveY); }
	Vector2 GetMove2() { return Vector2(m_MoveX2, m_MoveY2); }
	bool	IsTrigger(void) { return m_bTrigger; }
	
};