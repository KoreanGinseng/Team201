/*****************************************************************
 *	@file			Player.h
 *	@brief			プレイヤークラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Character.h"
#include	"Enemy.h"
//#include	"Object.h"
#include	"TargetObj.h"
#include	"Substance.h"
#include	"Score.h"

//DEFINE
#define		PLAYER_RECTDIS		40

class CPlayer : public CCharacter
{
private:

	typedef enum tag_WAY {
		WAY_LEFT,
		WAY_RIGHT,
	}WAY;

	std::vector<CSubstance*>	m_SkillTarget;
	bool						m_bTrigger;
	bool						m_bClime;
	int							m_HP;
	int							m_Target;
	float						m_CoolTime;
	float						m_Skillrang;
	CCircle						m_SkillCircle;
	int							m_DamageWait;

	void PadOparation(void);
	void KeyOparation(void);

	void Move(void);
	void MoveAdd(WAY w);
	void MoveSub(WAY w);
	void Animation(void);
	void Jump(void);

	enum tag_Animation {
		ANIM_WAIT,
		ANIM_MOVE,

		ANIM_COUNT,
	};

public:
	CPlayer(void);
	~CPlayer(void);
	void Initialize(void);
	void Update(void);
	void Render(Vector2 screenPos);
	void RenderDebug(Vector2 screenPos);
	void Release(void);
	

	//Skill
	void Skill(void);
	void SkillColision(CEnemy* pene, int eneCount, CTargetObj* pobj, int objCount);
	void TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray);

	//Collision
	void CollisionStage(Vector2 o);

	//Get
	bool	IsTrigger(void) { return m_bTrigger; }
	int		GetHp(void) { return m_HP; }
	//Set
	void   SetClime(const bool& b) { m_bClime = b; }


	bool   Dmg(CEnemy& ene);
};

